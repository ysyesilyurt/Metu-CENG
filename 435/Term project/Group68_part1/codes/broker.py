#!/usr/bin/env python

import socket  # for python Socket API
import struct # used in encoding messages

# Broker node

if __name__ == "__main__":

	# host = listen address for broker from source
	host = ("10.10.1.2", 10000) 

	# r1_addr = listen address for router1 from broker
	r1_addr = ("10.10.2.2", 10001)

	# r2_addr = listen address for router2 from broker
	r2_addr = ("10.10.4.2", 10002) 

	# Creates an IPV4 socket with UDP for communication between broker and r1
	sock_r1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  

	# Creates an IPV4 socket with UDP for communication between broker and r2
	sock_r2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# Creates an IPv4 socket with TCP to listen from source
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	# Changes listening socket's flag to not to be blocked by OS for port security reasons 
	sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	# Binds listening (TCP) socket to listen address from source (host)
	sock.bind(host)   

	# Starts listening from source (5 means at most 5 connection at a time can be queued, others will be dropped)
	sock.listen(5)
	print "TCP Listening on", host

	# Accepts source's connection
	source_socket, source_addr = sock.accept()
	print "Connection from = " + source_addr[0] + ":" + str(source_addr[1])

	# Listen for messages indefinitely, when a message comes first break it to 128 byte chunks
	# and packatize them with a sequence number to be able to order them on the destination
	# Then send them to either router1 or router2 according to their sequence numbers

	# Sequence number, initially = 0
	i=0

	while True:
		try:
			# listen from source (get byte streams with TCP socket)
			msg = source_socket.recv(1032) # expect 1032 bytes since packet also contains 8 bytes time information
			
			# if connection is closed, pass that information to r1 and r2 and terminate
			if msg == "" or msg is None: 
				print "Closing connection..."
				sock_r1.sendto("", r1_addr)
				sock_r2.sendto("", r2_addr)
				break
			# extract time information from packet
			time_old = struct.unpack("d", msg[:8])[0]

			# get original data
			msg = msg[8:]

			# start breaking data as 128 byte chunks
			part = msg[:128] 
			while part:
				print "Broker forwarding data to " + ["R1", "R2"][i%2] + " with seqnum= " + str(i) 

				# if seqnum even then send that packet to destination via r1 with embedding seqnum (send with UDP socket)
				if i % 2 == 0:
					part = struct.pack("i", i) + struct.pack("d", time_old) + part  
					sock_r1.sendto(part, r1_addr)

				# if seqnum odd then send that packet to destination via r2 with embedding seqnum (send with UDP socket)
				else:
					part = struct.pack("i", i) + struct.pack("d", time_old) + part
					sock_r2.sendto(part, r2_addr)

				# increment seqnum and get new chunk
				i+=1
				part = msg[(128 * (i % 8)) : (128 * ((i % 8) + 1))]

				if i % 8 == 0:
					break

		except KeyboardInterrupt:
			print "Exitting..."
			break
