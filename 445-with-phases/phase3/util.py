#!/usr/bin/env python3
from ast import literal_eval
import multiprocessing
import socket
import parser
import threading

collectorPort = 5140
UDSAddr = "./UDS"
database = "db.sqlite3"


class InvalidNodeAddress(Exception):
    pass


class Node(dict):
    """Represents a binary tree node.
    """

    def __init__(self, nodeID=1, value=None, left=None, right=None):
        super().__init__()
        self.__dict__ = self
        self.id = nodeID
        self.value = value
        self.left = left
        self.right = right

    # Return node at given address
    def getNode(self, address):
        if address == ():
            return self
        else:
            tmp = self
            for step in address:
                if step == 0:
                    if tmp.left is not None:
                        tmp = tmp.left
                    else:
                        raise InvalidNodeAddress("Could not find node at given address:", address)
                elif step == 1:
                    if tmp.right is not None:
                        tmp = tmp.right
                    else:
                        raise InvalidNodeAddress("Could not find node at given address:", address)
                else:
                    raise InvalidNodeAddress("Invalid address:", address)
            return tmp

    def dump(self, path=()):
        ret = ((path, self.value), )
        if self.left:
            ret += self.left.dump(path + (0, ))
        if self.right:
            ret += self.right.dump(path + (1, ))
        return ret

    def load(self, dump):
        for row in dump:
            rule_id = row[0]
            if row[1] == "AND" or row[1] == "OR":
                match = row[1]
            else:
                match = literal_eval(row[1])
            path = reverseAddress(rule_id)
            self.insert(path, match)

    def insert(self, path, match):
        # print(path, match)
        road = path
        dst = self
        while road:
            if road[0] == 0:
                if dst.left is None:
                    dst.left = Node(dst.id * 2)
                dst = dst.left
            elif road[0] == 1:
                if dst.right is None:
                    dst.right = Node(dst.id * 2 + 1)
                dst = dst.right
            else:
                raise InvalidNodeAddress("Invalid address:", path)
            road = road[1:]

        dst.value = match

    def loadJSON(self, dict_):
        if type(dict_["value"]) == list:
            self.value = tuple(dict_["value"])
        else:
            self.value = dict_["value"]
        if dict_["left"]:
            self.left = Node().loadJSON(dict_["left"])
        if dict_["right"]:
            self.right = Node().loadJSON(dict_["right"])
        return self


def resolveAddress(address):
    nodeID = 1
    for a in address:
        nodeID = nodeID * 2 + (a ^ 0)
    return nodeID


def reverseAddress(nodeID):
    address = []
    while nodeID > 1:
        if nodeID % 2 == 0:
            address.append(0)
        else:
            address.append(1)
        nodeID //= 2
    address.reverse()
    return tuple(address)


class LogCollector(multiprocessing.Process):
    def __init__(self, hostAddress, port, pipe):
        super(LogCollector, self).__init__(daemon=True)
        self.hostAddress = hostAddress
        self.port = port
        self.pipe = pipe

    def run(self):
        logParser = parser.Parser(True)
        collectorSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        collectorSock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        collectorSock.bind((self.hostAddress, self.port))

        try:
            while True:
                data, addr = collectorSock.recvfrom(4096)
                payload = logParser.parse(data.decode().rstrip())
                self.pipe.send(payload)
        except KeyboardInterrupt:
            exit()


class LogWatchTracker:
    def __init__(self, process, pipe):
        self.process = process
        self.pipe = pipe
        self.lock = threading.Lock()


class SocketBuffer:
    def __init__(self, sock, addr):
        self.sock = sock
        self.addr = addr

    def recv(self):
        return self.sock.recv(4096).decode().rstrip()

    def read(self):
        return self.sock.recv(4096).decode().rstrip().split("\n")

    def send(self, data):
        self.sock.send(data.rstrip().encode())

    def write(self, data):
        self.sock.send("\n".join(data).encode())


class UDSBuffer(SocketBuffer):
    def __init__(self):
        self.sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        self.sock.connect(UDSAddr)
        super(UDSBuffer, self).__init__(self.sock, UDSAddr)
