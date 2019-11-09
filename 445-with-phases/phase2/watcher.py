#!/usr/bin/env python3
import ipaddress
import json
import parser
import re
from util import *
from syslog_rfc5424_parser.constants import SyslogSeverity, SyslogFacility


class LogWatch:
    """LogWatch class for watching log sources
    match -> (matchfield, operator, value, negated, caseinsens)
    matchfield -> one of (WHOLE, IP, SEVERITY, FACILITY, FIELD:range:sep, RE:regexp:field)
    """
    def __init__(self, filename=None):
        self.rules = Node()
        self.logFile = filename
        self.logSource = None
        self.filteredLogs = []
        self.observerList = []

    # TODO: Add a UDP socket to recvfrom from remote log sources as well as the local ones as 4096 bytes
    def run(self):
        self.logSource = open(self.logFile, "rb")
        logParser = parser.Parser()
        line = self.logSource.readline()
        while line:
            payload = logParser.parse(line.decode(), False)
            if self.applyFilters(self.rules, payload):
                self.filteredLogs.append(line)
                self.notify(line)
            line = self.logSource.readline()
        self.logSource.close()

    def applyFilters(self, rules, payload):
        if rules.value == "AND":
            return self.applyFilters(rules.left, payload) and self.applyFilters(rules.right, payload)
        elif rules.value == "OR":
            return self.applyFilters(rules.left, payload) or self.applyFilters(rules.right, payload)
        else:
            return self.applyRule(rules.value, payload)

    def applyRule(self, rule, payload):
        if rule is None:
            return None

        class InvalidMatchfield(Exception):
            pass

        class InvalidOperator(Exception):
            pass

        def applyMatch(operand):
            arg1 = value
            arg2 = operand

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
                ret = re.match(arg1, arg2) is not None
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
            if re.match('\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}', value) and re.match('\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}', payload["hostname"]):
                value = ipaddress.IPv4Address(value)
                return applyMatch(ipaddress.IPv4Address(payload["hostname"]))
            elif type(value) == str and type(payload["hostname"] == str):
                return applyMatch(payload["hostname"])
            else:
                return False

        # emerg is the highest, debug is the lowest severity
        elif matchfield == "SEVERITY":
            if type(value) == str:
                if caseinsens:
                    value = value.lower()
                elif value != value.lower():
                    return False
                value = 7 - SyslogSeverity[value]
            severity = 7 - SyslogSeverity[payload["severity"]]
            return applyMatch(severity)

        # kern is the highest(0), unknown is the lowest (-1), if unknown is not present local7 is the lowest (23)
        elif matchfield == "FACILITY":
            if type(value) == str:
                if caseinsens:
                    value = value.lower()
                elif value != value.lower():
                    return False
                value = 23 - SyslogFacility[value]
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

    # Register given observer
    def register(self, obs):
        self.observerList.append(obs)

    # Unregister given observer
    def unregister(self, obs):
        try:
            self.observerList.remove(obs)
        except:
            raise NotAnObserverError("{0} is not an Observer of Logwatcher".format(obs))

    # Notify all observers when a new filtered log comes
    def notify(self, log):
        for observer in self.observerList:
            observer.update(self, log)

    # Set addressed Node to given "match" value.
    def setMatch(self, match, address = ()):
        self.rules.getNode(address).value = match

    # Set the the addressed node to given "connector" value. ("AND" or "OR")
    # Left branch of connector will be the previous node's match value, right branch will be the new match value.
    def combineMatch(self, match, connector, address = ()):
        node = self.rules.getNode(address)
        temp = node.value
        node.value = connector
        node.left = Node(temp)
        node.right = Node(match)

    # Delete the node at given address, the sibling of the node will replace the parent logical operator.
    def delMatch(self, address = ()):
        # Deleting the rules
        if address == ():
            if self.rules.left is None and self.rules.right is None:
                self.rules.value = None
                self.rules.left = None
                self.rules.right = None
        else:
            parentNode = self.rules.getNode(address[:-1])
            if address[-1] == 0:
                survivorNode = parentNode.right
            elif address[-1] == 1:
                survivorNode = parentNode.left
            else:
                raise AddressNotFoundError("Invalid address:", address)
            parentNode.value = survivorNode.value
            parentNode.left = survivorNode.left
            parentNode.right = survivorNode.right

    # Save current configuration as JSON to a file
    # Configuration -> log source path + rule tree
    def save(self, name):
        if not name.endswith(".json"):
            name += ".json"
        data = {"logFile": self.logFile, "rules": self.rules}
        with open(name, "w") as writeFile:
            json.dump(data, writeFile, indent = 4)

    # Load configuration from JSON file
    def load(self, name):
        if not name.endswith(".json"):
            name += ".json"
        with open(name, "r") as readFile:
            data = json.load(readFile)
        self.logFile = data["logFile"]
        self.rules.load(data["rules"])
