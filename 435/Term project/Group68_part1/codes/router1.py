#!/usr/bin/env python

import socket  # for python Socket API
import struct # used in decoding messages

# Router1 node

if __name__ == "__main__":

	# host = listen address for r1 from broker
	host = ("10.10.2.2", 10001) 

	# server = listen address for destination from r1
	server = ("10.10.3.2", 10003) 

	# Creates an IPV4 socket with UDP for communication between r1 and destination
	sock_server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 

	# Creates an IPv4 socket with UDP to listen from broker
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# Changes listening socket's flag to not to be blocked by OS for port security reasons 
	sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	# Binds listening socket to listen address from broker (host)
	sock.bind(host) 
	print "UDP Listening on", host

	# Listen for messages indefinitely, when a message comes forward it to destination.

	while True:
		try:
			msg = sock.recv(1024) 
			if msg == "" or msg is None:  # if connection is closed, pass that information to destination and terminate
				print "Closing connection..."
				sock_server.sendto("", server)
				break
			print "Router1 routing to server", struct.unpack("i", msg[:4])[0]
			sock_server.sendto(msg, server)  # send packet to destination
		except KeyboardInterrupt:
			print "Exitting..."
			sock_server.sendto("", server)
			break
