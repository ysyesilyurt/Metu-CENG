#!/usr/bin/env python

import hashlib # used for generating md5 Checksums
import socket # for python Socket API
import struct  # used in encoding messages
import time  # used to generate timestamps

# Source node

if __name__ == "__main__":

	# broker_addr = listen address for broker from source
	brokerAddr = ("10.10.1.2", 10000)
	
	# Creates an IPv4 socket with TCP for connection between source and broker 
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	
	# Establishes connection between source and broker
	sock.connect(brokerAddr)
	print "Connected to", brokerAddr

	# Opens input file from "input.txt" file for calculation of file md5sum
	with open("input.txt", "rb") as inputFile:
		# Creates a md5sum variable for file
		md5ChecksumFile = hashlib.md5()
		# Iteratively calculate md5checksum of file
		for chunk in iter(lambda: inputFile.read(500000), b""):
			md5ChecksumFile.update(chunk)

		packedChecksum = struct.pack("32s",md5ChecksumFile.hexdigest()) 

	# Opens input file again for reading and sending it to broker
	with open("input.txt", "rb") as inputFile:
		# Read 500KB data from file
		data = inputFile.read(500000)
		# Insert checksum of file and sending process's start time 
		# to the beginning of very first data packet
		startTime = struct.pack("d", time.time())
		data = packedChecksum + startTime + data
		while data != b'':
			print "Sending DATA to destination"
			# Send data to broker over TCP socket
			sock.sendall(data)
			# Read 500KB data from file
			data = inputFile.read(500000) 

	print "Terminating process..."
	
