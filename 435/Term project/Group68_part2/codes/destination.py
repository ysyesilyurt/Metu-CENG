#!/usr/bin/env python

import hashlib # used for generating md5 Checksums
import socket # for python Socket API
import struct  # used in decoding and encoding messages
import threading # used for multithreaded structure
import time  # used to generate timestamps

# Destination node

## Notice that, RDT protocol implemented here is reusable for any topology 
## or any network configuration based bandwidth, delay, and packet size.
## In case of changing of above values, one can just alter the addresses 
## of the destination interfaces with configuring routers correctly.
## In addition, Note that since RDT protocol implemented here sends feedbacks packets as 
## 47 bytes (actually with Ethernet, IP and UDP headers it is 89 bytes)
## It will never send more data than 1000 bytes (max packet size of a packet in RDT protocol here) 

if __name__ == "__main__":

	# host1 = listen address for destination from interface to router1
	host1 = ("10.10.3.2", 10001)

	# host2 = listen address for destination from interface to router2
	host2 = ("10.10.5.2", 10001)

	# b1Addr = listen address of broker's first (r1) interface
	b1Addr = ("10.10.2.1", 10000)

	# b2Addr = listen address of broker's first (r2) interface
	b2Addr = ("10.10.4.1", 10000)

	# Creates an IPv4 socket with UDP to listen data pkts from host1
	sock1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# Changes listening socket's flag to not to be blocked by OS for port security reasons 
	sock1.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	# Binds listening socket to host1
	sock1.bind(host1) 

	# Creates an IPv4 socket with UDP to listen data pkts from host2
	sock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# Changes listening socket's flag to not to be blocked by OS for port security reasons
	sock2.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	# Binds listening socket to host2
	sock2.bind(host2) 

	# Creates an IPV4 socket with UDP for communication between destination and b1Addr
	outSock1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# Creates an IPV4 socket with UDP for communication between destination and b2Addr
	outSock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	print "Listening on", host1
	print "Listening on", host2

	# Two lists used for storing incoming data temporarily
	data1 = [] # for packets that came from interface-1 (host1)
	data2 = [] # for packets that came from interface-2 (host2)

	# Initially expectedSeqnum = 0
	expectedSeqnum = 0
	# Lock for expectedSeqnum which is a shared variable among threads
	seqLock = threading.Lock()

	def handler(listenSock, outSock, sendAddr, data):
		'''A generic function for handling of the data pkts upon their arrival
		   If receives a data packet correctly, sends and Acknowledgement packet back to broker
		'''
		global expectedSeqnum
		while True:
			try:
				# Listen from interfaces
				msg = listenSock.recv(1000) # Expect maximum 1000 bytes
				if msg == "" or msg is None: # terminate connection
					outSock.sendto("", sendAddr) 
					break

				# extract md5 checksum
				checksum = struct.unpack("32s", msg[:32])[0]
				pkt = msg[32:]
				# calculate packet checksum
				packetChecksum = hashlib.md5(pkt).hexdigest()
				
				# extract time information
				timeOld = struct.unpack("d", pkt[:8])[0]
				# extract sequence number
				seq = struct.unpack("i", pkt[8:12])[0]
				pkt = pkt[12:]

				with seqLock:
					# if packet hasseqnum == expectedSeqnum and packet is notCorrupt; then send ACK pkt for the data packet
					if packetChecksum == checksum:	
						if seq == expectedSeqnum:
							# append data to the data list	
							data.append([seq, pkt])
							print "Received a data correctly, sending an ACK back to broker with expectedSeqnum:", expectedSeqnum

							# pack old time, sequence number and data
							sendPkt = struct.pack("d", timeOld) + struct.pack("i", expectedSeqnum) + b"ACK"  
							# calculate checksum  
							ackChecksum = hashlib.md5(sendPkt).hexdigest()
							# embed to packet; now packet has; 32 + 4 + 900 = 936 bytes
							sendPkt = struct.pack("32s", ackChecksum) + sendPkt 
							# send ACK packet to broker
							outSock.sendto(sendPkt, sendAddr)  
							# increment expectedSeqnum
							expectedSeqnum += 1
					
						# else; discard data
					else:
						print "OOPS, corrupt data packet.."

			except KeyboardInterrupt:
				outSock.sendto("", sendAddr) 
				print "Exitting..."
				break

	# Since destination needs to listen from 2 interfaces at the same time
	# A thread for handling incoming messages from interface-1 (r1) gets created and sent to 'handler'
	# function with proper parameters 
	r1_handler = threading.Thread(target=handler,args=(sock1, outSock1, b1Addr, data1))
	r1_handler.start()

	# Main execution will listen incoming messages from interface-2 (r2)
	handler(sock2, outSock2, b2Addr, data2)

	# Wait implicitly for r1_handler to finish
	r1_handler.join()

	# Combine arrived data from 2 lists
	data = data1 + data2

	# Receive file checksum at the end
	print "Waiting for Checksum of file to arrive.."
	msg = sock1.recv(1000)
	fileChecksum = struct.unpack("32s", msg[:32])[0]
	startTime = struct.unpack("d", msg[32:40])[0]
	
	print "File sending process took:", time.time() - startTime

	# and order them according to their sequence numbers; Be sure that data is in Correct Order
	data.sort()

	# Save them to a file named "output.txt"
	with open("output.txt", "wb") as outputFile:
		for i in data:
			outputFile.write(i[1]) 

	# Open "output.txt" file and read chunk by chunk to calculate its md5sum 
	with open("output.txt", "rb") as outputFile:
		calculatedChecksum = hashlib.md5()
		# Iteratively calculate md5checksum of file
		for chunk in iter(lambda: outputFile.read(500000), b""):
			calculatedChecksum.update(chunk)

	# Check if file is transferred correctly
	if fileChecksum == calculatedChecksum.hexdigest():
		print "File is transferred correctly (md5Cheksums match).."
	else:
		print "OOPS, checksums does not match; file is not received correctly!"
	
	print "Terminating process..."