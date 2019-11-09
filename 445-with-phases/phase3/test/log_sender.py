#!/usr/bin/env python3

import socket
import sys
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server = ("localhost", 5140)

with open(sys.argv[1], "br") as log_source:
    log = log_source.readline()
    while log:
        sock.sendto(log, server)
        time.sleep(0.5)
        log = log_source.readline()