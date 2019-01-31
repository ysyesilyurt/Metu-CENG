#!/usr/bin/env python

import socket # for python Socket API
import time  # used to generate timestamps
import struct  # used in decoding messages
from threading import Thread # used for multithreaded structure

# Destination node

if __name__ == "__main__":

	# host1 = listen address for destination from r1
	host1 = ("10.10.3.2", 10003)

	# host2 = listen address for destination from r2
	host2 = ("10.10.5.2", 10003)

	# Creates an IPv4 socket with UDP to listen from r1
	sock1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# Changes listening socket's flag to not to be blocked by OS for port security reasons 
	sock1.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	# Binds listening socket to listen address from r1 (host1)
	sock1.bind(host1) 

	# Creates an IPv4 socket with UDP to listen from r2
	sock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# Changes listening socket's flag to not to be blocked by OS for port security reasons
	sock2.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	# Binds listening socket to listen address from r2 (host2)
	sock2.bind(host2) 

	print "Listening on", host1
	print "Listening on", host2

	# Two lists used for calculating avg e2e delay between source and destination
	delta1 = [] # for packets that came from r1
	delta2 = [] # for packets that came from r2

	# Two lists used for storing incoming data temporarily
	data1 = [] # for packets that came from r1
	data2 = [] # for packets that came from r2

	# handler function for listening for incoming packages and handling their storage issues
	# when a message arrives calculate the time difference between the current time and the timestamp on the package
	# then append it to 'delta' list and append incoming data to 'data' list
	def handler(sock, delta, data):
		while True:
			try:
				msg = sock.recv(1024)
				if msg == "" or msg is None: # terminate connection
					break

				# extract sequence number
				seq = struct.unpack("i", msg[:4])[0]

				# check if whole packet came (1024 bytes)
				if not (seq + 1) % 8: 
					# calculate e2e delay and append it to the delta list
					delta.append(time.time() - struct.unpack("d", msg[4:12])[0])
					print "Received DATA within {}ms".format(delta[-1] * 1000)

				# append data to the data list	
				data.append([seq, msg[12:]])
			except KeyboardInterrupt:
				print "Exitting..."
				break

	# Since destination needs to listen from 2 nodes (r1 and r2) at the same time
	# A thread for handling incoming messages from r1 gets created and sent to 'handler'
	# function with proper parameters 
	r1_handler = Thread(target=handler,args=(sock1, delta1, data1))
	r1_handler.start()

	# Main execution will listen incoming messages from r2
	handler(sock2, delta2, data2)

	# Wait implicitly for r1_handler to finish
	r1_handler.join()

	# Calculate average delay with getting the mean of total delays
	print "Avg e2e:", (sum(delta1 + delta2) / len(delta1 + delta2)) * 1000 , "ms"

	# Combine arrived data from 2 lists
	data = data1 + data2

	# and order them according to their sequence numbers
	data.sort()

	# Save them to a file named "sensor_readings.txt"
	with open("sensor_readings.txt", "wb") as output_file:
		for i in data:
			output_file.write(i[1])
	 
	print "Closing connection..."
