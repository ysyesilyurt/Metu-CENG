#!/usr/bin/env python3

import time
import sys
import socket

# ysyesilyurt

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server = ("localhost",5140)

with open(sys.argv[1], "rb") as log_source:
    log = log_source.readline()

    while log != b'':
        sock.sendto(log,server)
        time.sleep(1)
        log = log_source.readline()

