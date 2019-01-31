#!/usr/bin/env python

import socket # for python Socket API
import time  # used to generate timestamps
import struct  # used in encoding messages

# Source node

if __name__ == "__main__":

	# broker_addr = listen address for broker from source
	broker_addr = ("10.10.1.2", 10000)
	
	# Creates an IPv4 socket with TCP for connection between source and broker 
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	
	# Establishes connection between source and broker
	sock.connect(broker_addr)
	print "Connected to", broker_addr

	# Opens sensor readings from "readings.txt" file
	with open("readings.txt", "rb") as sensor_readings:
		# Reads data from file as 1024 bytes
		data = sensor_readings.read(1024)

		# File contains 102400 bytes = 1024 * 100, so this loop will execute 100 times
		while data != b'':
			print "Sending DATA to destination"
			# Embeds current time information into the packet to be sent
			msg = struct.pack("d", time.time()) + data
			# Sends packet to broker
			sock.sendall(msg)
			# Wait 1 second for other nodes to get ready again
			time.sleep(1)
			data = sensor_readings.read(1024)