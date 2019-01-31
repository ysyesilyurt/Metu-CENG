#!/usr/bin/env python

import hashlib # used for generating md5 Checksums
import socket  # for python Socket API
import struct # used in encoding and decoding messages
import threading # multithreaded structure
import time # used for timeout calculations

# Broker node

## Notice that, RDT protocol implemented here is reusable for any topology 
## or any network configuration based bandwidth, delay, and packet size.
## In case of changing of above values, one can just alter the addresses 
## of the destination interfaces with configuring routers correctly.
## In addition, Note that since RDT protocol implemented here sends data packets as 
## 944 bytes (actually with Ethernet, IP and UDP headers it is 986 bytes)
## It will never send more data than 1000 bytes (max packet size of a packet in RDT protocol here) 

if __name__ == "__main__":

	# host = listen address for broker from source
	host = ("10.10.1.2", 10000) 

	# host2 = listen address for broker from interface to router1
	host2 = ("10.10.2.1", 10000) 

	# host3 = listen address for broker from interface to router2
	host3 = ("10.10.4.1", 10000) 

	# d1Addr = listen address of destination's first (r1) interface
	d1Addr = ("10.10.3.2", 10001)

	# d2Addr = listen address of destination's second (r2) interface
	d2Addr = ("10.10.5.2", 10001) 

	# Creates an IPV4 socket with UDP for communication between broker and d1Addr
	sockD1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  

	# Creates an IPV4 socket with UDP for communication between broker and d2Addr
	sockD2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# Creates an IPv4 socket with TCP to listen from source
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	# Changes listening socket's flag to not to be blocked by OS for port security reasons 
	sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	# Binds listening (TCP) socket to listen address from source (host)
	sock.bind(host)   

	# Creates an IPv4 socket with UDP to listen ACK packets from host2
	sockUdp1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# Changes listening socket's flag to not to be blocked by OS for port security reasons
	sockUdp1.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	# Binds listening socket to host2
	sockUdp1.bind(host2) 

	# Creates an IPv4 socket with UDP to listen ACK packets from host3
	sockUdp2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# Changes listening socket's flag to not to be blocked by OS for port security reasons
	sockUdp2.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	# Binds listening socket to host3
	sockUdp2.bind(host3) 

	# Starts TCP socket's listening from source (5 means at most 5 connection at a time can be queued, others will be dropped)
	sock.listen(5)
	print "TCP Listening on", host
	print "UDP Listening on", host2
	print "UDP Listening on", host3

	# Accepts source's connection
	source_socket, source_addr = sock.accept()
	print "TCP Connection from = " + source_addr[0] + ":" + str(source_addr[1])

	# data is for accumulating incoming data from source
	data = ""
	# buff is for storing pkts temporarily in a buffer for RDT
	buff = []
	# Sequence number and base, initially = 0
	seqnum = 0
	base = 0
	# Window size is set to 20
	windowSize = 20

	# timeout value is initially set to 0.5, it will be recalculated per incoming ACK packet 
	timeoutInterval = 0.5
	# estimatedRTT and devRTT initially set to timeoutInterval and 0, respectively.
	estimatedRTT = timeoutInterval
	devRTT = 0

	# set of locks for shared common variables 
	baseLock = threading.Lock()
	timerLock = threading.Lock()
	buffLock = threading.Lock()
	baseCond = threading.Condition()

	# flag for acquiring file checksum and initial transfer time
	first = False

	# First get whole data over TCP socket from source in 500KB chunks
	while True:
		pkt = source_socket.recv(500000) 
		if not pkt:
			break
		# If this is first packet coming, extract checksum of file and time information from it
		if not first:
			md5Sum = pkt[:32]
			startTime = pkt[32:40]
			pkt = pkt[40:]
			first = True
		data += pkt

	# Then divide it to 900 byte chunks and store in buffer
	while data:
		buff.append(data[0:900])
		data = data[900:]

	def recvHandler(udpRecvSock): 
		'''Function for handling incoming ACK pkts from destination'''
		global base, timer
		while True:
			try:
				# listen from interfaces
				msg = udpRecvSock.recv(1000) # expect a maximum of 1000 bytes
				if msg == "" or msg is None: # terminate connection 
					break

				# extract md5sum
				checksum = struct.unpack("32s", msg[:32])[0]
				pkt = msg[32:]
				# calculate packet checksum
				packetChecksum = hashlib.md5(pkt).hexdigest()

				# if ACK packet is not corrupt
				if packetChecksum == checksum:
					# extract time information
					timeOld = struct.unpack("d", pkt[:8])[0]
					# extract sequence number 
					seq = struct.unpack("i", pkt[8:12])[0]

					# slide base (acknumOfPkt + 1) indices
					with baseLock:
						if seq + 1 > base:
							base = seq + 1
					with baseCond:
						# Notify waiting threads
						baseCond.notify()
					print "Received a correct ACK packet from destination with seqnum:", seq
					with timerLock:
						with baseLock:
							# If base equals to current sequence number; stop timer
							if base == seqnum:
								timer.cancel()
							# Else; start timer
							else:
								timer.cancel()
								# calculate new sampleRTT 
								sampleRTT = time.time() - timeOld
								# calculate new timeout interval value
								timeoutInterval = calcTimeoutInterval(sampleRTT)
								# Start timer again (with newly calculated timeout value)
								timer = threading.Timer(timeoutInterval, retransmitHandler) 
								timer.start() 
				else:
					# else; packet is corrupt; wait for timeout
					print "OOPS.., Received a corrupt ACK packet.." 

			except KeyboardInterrupt:
				print "Exitting..."
				sockD1.sendto("", d1Addr)
				sockD2.sendto("", d2Addr)
				break

	def sendHandler():
		'''Function for handling sending of data pkts to destination'''
		global buff,base,timer,seqnum
		while True:
			try:
				with buffLock:
					if seqnum == len(buff):
						# if sending process is done; pass that information to destination and terminate
						sockD1.sendto("", d1Addr)
						sockD2.sendto("", d2Addr)
						break
				with baseLock:
					tempBase = base
				# if sequence number is within the bounds of window size; send data
				if seqnum < tempBase + windowSize: 
					with buffLock:
						# get new part from buffer
						part = buff[seqnum]
					print "Broker sending data to destination with seqnum:", seqnum 

					# if seqnum is even then send that packet to destination to d1 interface (via r1)
					# with embedding seqnum and checksum
					if seqnum % 2 == 0:
						# pack current time, sequence number and data
						part = struct.pack("d", time.time()) + struct.pack("i", seqnum) + part
						# calculate checksum  
						checksum = hashlib.md5(part).hexdigest()
						# embed to packet; now packet has; 32 + 4 + 900 = 936 bytes
						part = struct.pack("32s", checksum) + part 
						sockD1.sendto(part, d1Addr)

					# if seqnum is odd then send that packet to destination to d2 interface (via r2)
					# with embedding seqnum and checksum
					else:
						# pack current time, sequence number and data
						part = struct.pack("d", time.time()) + struct.pack("i", seqnum) + part
						# calculate checksum  
						checksum = hashlib.md5(part).hexdigest()
						# embed to packet; now packet has; 32 + 4 + 900 = 936 bytes
						part = struct.pack("32s", checksum) + part 
						sockD2.sendto(part, d2Addr)

					if tempBase == seqnum:
						# For initial case; start timer 
						with timerLock:
							timer.cancel()
							timer = threading.Timer(timeoutInterval, retransmitHandler) 
							timer.start()

					# increment seqnum
					seqnum += 1

				# else; wait for base to slide
				else:
					with baseCond:
						print "Waiting for base to slide.."
						baseCond.wait()

				# Wait for network to process sent data
				time.sleep(0.02)

			except KeyboardInterrupt:
				print "Exitting..."
				sockD1.sendto("", d1Addr)
				sockD2.sendto("", d2Addr)
				break

	def retransmitHandler(): 
		'''Function for handling fast retransmission in case of timeout'''
		with buffLock:
			with timerLock:
				# Start timer again
				timer = threading.Timer(timeoutInterval, retransmitHandler) 
				timer.start()
				with baseLock: 
					print "Timeout for packet:", base
					# Retransmit all UnAcked packets back
					# starting from base to seqnum 
					for i in range(base,seqnum):
						try:
							# get new part of the buffer
							part = buff[i]
							print "Retransmitting packet with seqnum:", i
							# if seqnum is even then send that packet to destination to d1 interface (via r1) 
							# with embedding seqnum and checksum
							if i % 2 == 0:
								# pack current time, sequence number and data
								part = struct.pack("d", time.time()) + struct.pack("i", i) + part
								# calculate checksum  
								checksum = hashlib.md5(part).hexdigest()
								# embed to packet; now packet has; 32 + 4 + 900 = 936 bytes
								part = struct.pack("32s", checksum) + part 
								sockD1.sendto(part, d1Addr)
							# if seqnum is odd then send that packet to destination to d2 interface (via r2)
							# with embedding seqnum and checksum
							else:
								# pack current time, sequence number and data
								part = struct.pack("d", time.time()) + struct.pack("i", i) + part
								# calculate checksum  
								checksum = hashlib.md5(part).hexdigest()
								# embed to packet; now packet has; 32 + 4 + 900 = 936 bytes
								part = struct.pack("32s", checksum) + part 
								sockD2.sendto(part, d2Addr)

							# Wait for threads to process sent data
							time.sleep(0.02)

						except KeyboardInterrupt:
							print "Exitting..."
							break

	def calcTimeoutInterval(sampleRTT):
		"""Function for calculation of timeout value based on sample, estimated and devRTT values"""
		global estimatedRTT, devRTT
		estimatedRTT = (0.875 * estimatedRTT) + (0.125 * sampleRTT)
		devRTT = (0.75 * devRTT) + (0.75 * abs(sampleRTT - estimatedRTT))
		return estimatedRTT + (4 * devRTT)

	# Set initial timer
	timer = threading.Timer(timeoutInterval, retransmitHandler) 

	# Set 2 threads (for each interface) for listening incoming ACK pkts from destination
	rcvThread1 = threading.Thread(target=recvHandler,args=(sockUdp1,))
	rcvThread1.start()
	rcvThread2 = threading.Thread(target=recvHandler,args=(sockUdp2,))
	rcvThread2.start()

	# Call sending process in main execution
	sendHandler()

	# Wait implicitly for threads to finish their jobs
	rcvThread1.join()
	rcvThread2.join()

	# Wait for 2 seconds for destination to get ready again
	time.sleep(2)
	# Finally, send md5Sum of the file and file sending process's start time
	# (which are both received from source within the very first packet)
	print "Sending checksum and time information to destination.."
	sockD1.sendto((md5Sum + startTime),d1Addr)

	print "Terminating process..."