#!/usr/bin/env python3
from ast import literal_eval
import ipaddress
import multiprocessing
import os
import re
import selectors
import socket
import threading
import sqlite3
import sys
from util import *
from syslog_rfc5424_parser.constants import SyslogSeverity, SyslogFacility


class LogWatchManager:
    def __init__(self):
        self.logWatchTrackers = {}
        self.logWatchTrackersLock = threading.Lock()
        self.hostAddress = "localhost"
        self.selector = selectors.DefaultSelector()

    def start(self):
        self.initWatchers()
        self.startLogCollector()
        self.startServer()
        self.run()

    def run(self):
        try:
            while True:
                events = self.selector.select()
                for key, _ in events:
                    # collectorPipe
                    if key.data == 0:
                        payload = key.fileobj.recv()
                        with self.logWatchTrackersLock:
                            for lw in self.logWatchTrackers.values():
                                with lw.lock:
                                    lw.pipe.send(("log", payload))

                    # serverPipe: New client is connected.
                    elif key.data == 1:
                        sock, addr = key.fileobj.accept()
                        thread = threading.Thread(target=self.clientHandler, args=(sock, addr), daemon=True)
                        thread.start()
        except KeyboardInterrupt:
            exit()

    def clientHandler(self, sock, addr):
        methodsTable = {"create": self.createWatcher, "setMatch": self.setMatch, "combineMatch": self.combineMatch,
                        "delMatch": self.delMatch}

        data = sock.recv(4096).decode().split("\n")
        try:
            ret = methodsTable[data[0]](*data[1:])

            if ret:
                sock.send(b"0")
            else:
                sock.send(b"1")
        except Exception as e:
            sock.send(b"2")
            print("Log Watch Manager: {} ({})".format(e, addr))
        sock.close()

    def createWatcher(self, lwID=None, name=None, soft=False):
        with self.logWatchTrackersLock:
            if not lwID:
                lwID = len(self.logWatchTrackers)
            if not name:
                name = "Watcher {}".format(lwID)
            parent_conn, child_conn = multiprocessing.Pipe()
            process = LogWatch(lwID, name, child_conn)
            lwTracker = LogWatchTracker(process, parent_conn)
            self.logWatchTrackers[lwID] = lwTracker
            self.selector.register(parent_conn, selectors.EVENT_READ, lwTracker)
            if not soft:
                with sqlite3.connect(database) as conn:
                    c = conn.cursor()
                    c.execute("""insert into watcher_watchers (wid, name) values ({}, '{}');""".format(lwID, name))
                    c.execute("""insert into watcher_watcherrules(wid, rule_id, rule) values({}, {}, '{}')""".format(
                        lwID, 1, ()))
                print("{} created.".format(name), file=sys.stderr)
        process.start()
        print("{} started.".format(name), file=sys.stderr)
        return True

    def setMatch(self, lwID, match, address):
        lwID = int(lwID)
        match = literal_eval(match)
        address = literal_eval(address)
        with self.logWatchTrackersLock:
            lw = self.logWatchTrackers[lwID]
        with lw.lock:
            lw.pipe.send(("setMatch", match, address))
            response = lw.pipe.recv()
        if response == "0":
            return True
        else:
            return False

    def combineMatch(self, lwID, match, connector, address):
        lwID = int(lwID)
        match = literal_eval(match)
        connector = connector
        address = literal_eval(address)
        with self.logWatchTrackersLock:
            lw = self.logWatchTrackers[lwID]
        with lw.lock:
            lw.pipe.send(("combineMatch", match, connector, address))
            response = lw.pipe.recv()
        if response == "0":
            return True
        else:
            return False

    def delMatch(self, lwID, address):
        lwID = int(lwID)
        address = literal_eval(address)
        with self.logWatchTrackersLock:
            lw = self.logWatchTrackers[lwID]
        with lw.lock:
            lw.pipe.send(("delMatch", address))
            response = lw.pipe.recv()
        if response == "0":
            return True
        else:
            return False

    def initWatchers(self):
        with sqlite3.connect(database) as conn:
            c = conn.cursor()
            watchers = c.execute("""select wid, name from watcher_watchers;""").fetchall()

        for watcher in watchers:
            self.createWatcher(watcher[0], watcher[1], soft=True)

    def startLogCollector(self):
        collectorPipe, externalPipe = multiprocessing.Pipe()
        collector = LogCollector(self.hostAddress, collectorPort, externalPipe)
        collector.start()
        self.selector.register(collectorPipe, selectors.EVENT_READ, 0)

    def startServer(self):
        try:
            os.unlink(UDSAddr)
        except OSError:
            if os.path.exists(UDSAddr):
                raise

        sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.bind(UDSAddr)
        sock.listen(10)
        self.selector.register(sock, selectors.EVENT_READ, 1)


class LogWatch(multiprocessing.Process):
    """LogWatch class for watching log sources
    match -> (matchfield, operator, value, negated, caseinsens)
    matchfield -> one of (WHOLE, IP, SEVERITY, FACILITY, FIELD:range:sep, RE:regexp:field)
    """

    def __init__(self, lwID, name, pipe):
        super(LogWatch, self).__init__(daemon=True)
        self.lwID = lwID
        self.name = name
        self.pipe = pipe
        self.rules = Node()
        self.logs = set()
        self.load()

    def run(self):
        while True:
            try:
                data = self.pipe.recv()
                if not data:
                    return
                if data[0] == "setMatch":
                    self.setMatch(*data[1:])
                elif data[0] == "combineMatch":
                    self.combineMatch(*data[1:])
                elif data[0] == "delMatch":
                    self.delMatch(*data[1:])
                elif data[0] == "log":
                    if self.applyFilters(self.rules, data[1].as_dict()):
                        self.logs.add(str(data[1]))
                        self.saveLog(str(data[1]))
                else:
                    raise Exception("Invalid LogWatch command")
                self.pipe.send("0")
            except Exception as e:
                print("Log Watch {} ({}): {}".format(self.lwID, self.name, e), file=sys.stderr)
                self.pipe.send("1")

    def applyFilters(self, rules, payload):
        if rules.value == "AND":
            return self.applyFilters(rules.left, payload) and self.applyFilters(rules.right, payload)
        elif rules.value == "OR":
            return self.applyFilters(rules.left, payload) or self.applyFilters(rules.right, payload)
        else:
            return self.applyRule(rules.value, payload)

    def applyRule(self, rule, payload):
        if not rule:
            return False

        class InvalidMatchfield(Exception):
            pass

        class InvalidOperator(Exception):
            pass

        def applyMatch(operand):
            arg1 = operand
            arg2 = value

            if caseinsens and type(operand) == str:
                arg1 = arg1.lower()
                arg2 = arg2.lower()
            if operator == "EQ":
                ret = arg1 == arg2
            elif operator == "LT":
                ret = arg1 < arg2
            elif operator == "LE":
                ret = arg1 <= arg2
            elif operator == "GT":
                ret = arg1 > arg2
            elif operator == "GE":
                ret = arg1 >= arg2
            elif operator == "RE":
                ret = re.match(arg2, arg1) is not None
            else:
                raise InvalidOperator("Invalid operator {0} in rule {1}".format(operator, rule))
            if not negated:
                return ret
            else:
                return not ret

        matchfield = rule[0]
        operator = rule[1]
        value = rule[2]
        negated = rule[3]
        caseinsens = rule[4]

        if matchfield == "WHOLE":
            return applyMatch(payload["msg"])

        elif matchfield == "IP":
            if re.match('\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}', value) and re.match('\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}',
                                                                                  payload["hostname"]):
                value = ipaddress.IPv4Address(value)
                return applyMatch(ipaddress.IPv4Address(payload["hostname"]))
            elif type(value) == str and type(payload["hostname"] == str):
                return applyMatch(payload["hostname"])
            else:
                return False

        # emerg is the highest, debug is the lowest severity
        elif matchfield == "SEVERITY":
            if type(value) == str:
                value = 7 - SyslogSeverity[value.lower()]
            else:
                value = 7 - value
            severity = 7 - SyslogSeverity[payload["severity"]]
            return applyMatch(severity)

        # kern is the highest(0), unknown is the lowest (-1), if unknown is not present local7 is the lowest (23)
        elif matchfield == "FACILITY":
            if type(value) == str:
                value = 23 - SyslogFacility[value.lower()]
            else:
                value = 23 - value
            facility = 23 - SyslogFacility[payload["facility"]]
            if facility == 24:
                facility = -1
            if value == 24:
                value = -1
            return applyMatch(facility)

        elif matchfield.startswith("FIELD:"):
            fieldSplitList = matchfield.split(':')
            fieldStartRange = int(fieldSplitList[1][0])
            delimiter = fieldSplitList[2]
            if len(fieldSplitList[1]) != 1:
                fieldEndRange = int(fieldSplitList[1][2:]) + 1
                return applyMatch(delimiter.join(payload["msg"].split(delimiter)[fieldStartRange:fieldEndRange]))
            else:
                return applyMatch("".join(payload["msg"].split(delimiter)[fieldStartRange]))

        elif matchfield.startswith("RE:"):
            regexSplitList = matchfield.split(':')
            regexp = regexSplitList[1]
            field = regexSplitList[2]
            return applyMatch(re.sub(regexp, '\g<' + field + '>', payload["msg"]))

        else:
            raise InvalidMatchfield("Invalid matchfield {0} in rule {1}".format(matchfield, rule))

    # Set addressed Node to given "match" value.
    def setMatch(self, match, address):
        node = self.rules.getNode(address)
        if node.left is not None or node.right is not None:
            raise InvalidNodeAddress("Cant set rule at LogWatch {} since address {} is not a leaf".format(self.lwID,
                                                                                                          address))
        node.value = match

        # Update database
        self.saveRules()

    # Set the the addressed node to given "connector" value. ("AND" or "OR")
    # Left branch of connector will be the previous node's match value, right branch will be the new match value.
    def combineMatch(self, match, connector, address):
        node = self.rules.getNode(address)
        if node.left is not None or node.right is not None:
            raise InvalidNodeAddress("Cant combine rule at LogWatch {} since address {} is not a leaf".format(self.lwID,
                                                                                                              address))
        temp = node.value
        node.value = connector
        node.left = Node(node.id * 2, temp)
        node.right = Node(node.id * 2 + 1, match)

        # Update database
        self.saveRules()

    # Delete the node at given address, the sibling of the node will replace the parent logical operator.
    def delMatch(self, address):
        if self.rules.getNode(address).value == "OR" or self.rules.getNode(address).value == "AND":
            raise InvalidNodeAddress("Cant delete rule at LogWatch {} since address {} is not a leaf".format(self.lwID,
                                                                                                             address))

        if address == ():
            self.rules.value = None
            self.rules.left = None
            self.rules.right = None
        else:
            parentNode = self.rules.getNode(address[:-1])
            if address[-1] == 0:
                survivorNode = parentNode.right
            else:
                survivorNode = parentNode.left

            parentNode.value = survivorNode.value
            parentNode.left = survivorNode.left
            parentNode.right = survivorNode.right

        # Update database
        self.saveRules()

    def saveLog(self, log):
        with sqlite3.connect(database) as conn:
            c = conn.cursor()
            c.execute("""insert into watcher_watcherlogs(wid, log) values({}, \"{}\")""".format(self.lwID, log))

    def saveRules(self):
        dump = self.rules.dump()
        with sqlite3.connect(database) as conn:
            c = conn.cursor()
            c.execute("""delete from watcher_watcherrules where wid == {};""".format(self.lwID))
            for row in dump:
                c.execute("""insert into watcher_watcherrules (wid, rule_id, rule) values ({}, {}, \"{}\")""".format(
                    self.lwID, resolveAddress(row[0]), row[1]))

    # Load configuration from database
    def load(self):
        with sqlite3.connect(database) as conn:
            c = conn.cursor()
            rules = c.execute("""select rule_id, rule from watcher_watcherrules where wid == {} order by rule_id;""".format(self.lwID)).fetchall()
            logs = c.execute("""select log from watcher_watcherlogs where wid == {};""".format(self.lwID)).fetchall()
        self.rules.load(rules)
        self.logs = set(logs)


if __name__ == "__main__":
    lwm = LogWatchManager()
    lwm.start()
