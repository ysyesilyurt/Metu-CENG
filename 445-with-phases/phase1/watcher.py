#!/usr/bin/env python3

from util import Node
import json
import os


def main():

    log_file = "/var/log/syslog"
    instance = LogWatch(log_file)
    tester(instance, log_file)

    print("Log source path of the object:", instance.log_source_path)
    print("Rule tree of the object:\n", json.dumps(instance.rule_tree, indent = 2))


def tester(instance, log_file):
    print("Initialized a LogWatch object with " + log_file + " file")
    assert instance.log_source_path == "/var/log/syslog"

    print("Constructing rule tree using setMatch and combineMatch")
    instance.setMatch(8)
    instance.combineMatch(6, "AND", ())
    assert instance.rule_tree.value == "AND"
    assert instance.rule_tree.left.value == 8 and instance.rule_tree.right.value == 6

    instance.combineMatch(5, "OR", (0,))
    instance.combineMatch(9, "OR", (0, 0))
    assert instance.rule_tree.value == "AND"
    assert instance.rule_tree.left.value == "OR" and instance.rule_tree.right.value == 6
    assert instance.rule_tree.left.left.value == "OR" and instance.rule_tree.left.right.value == 5
    assert instance.rule_tree.left.left.left.value == 8 and instance.rule_tree.left.left.right.value == 9

    tree_conf1 = "storage"
    print("Saving current configuration as " + tree_conf1 + ".json")
    instance.save(tree_conf1)
    assert os.path.exists(tree_conf1 + ".json") == 1

    print("Loading current configuration from " + tree_conf1 + ".json")
    instance.load(tree_conf1)
    # [AND,[OR,[OR,[8,[],[]],[9,[],[]]],[5,[],[]]],[6,[],[]]]
    assert instance.rule_tree.value == "AND"
    assert instance.rule_tree.left.value == "OR" and instance.rule_tree.right.value == 6
    assert instance.rule_tree.left.left.value == "OR" and instance.rule_tree.left.right.value == 5
    assert instance.rule_tree.left.left.left.value == 8 and instance.rule_tree.left.left.right.value == 9

    del_address = (0, 0, 1)
    print("Deleting node at " + str(del_address) + " address")
    instance.delMatch(del_address)
    # [AND,[OR,[8,[],[]],[5,[],[]],[6,[],[]]]
    assert instance.rule_tree.value == "AND"
    assert instance.rule_tree.left.value == "OR" and instance.rule_tree.right.value == 6
    assert instance.rule_tree.left.left.value == 8 and instance.rule_tree.left.right.value == 5

    tree_conf2 = "storage2"
    print("Saving current configuration as " + tree_conf2 + ".json")
    instance.save(tree_conf2)
    assert os.path.exists(tree_conf2 + ".json") == 1

    print("Loading current configuration from " + tree_conf2 + ".json")
    instance.load(tree_conf2)
    # [AND,[OR,[8,[],[]],[5,[],[]],[6,[],[]]]
    assert instance.rule_tree.value == "AND"
    assert instance.rule_tree.left.value == "OR" and instance.rule_tree.right.value == 6
    assert instance.rule_tree.left.left.value == 8 and instance.rule_tree.left.right.value == 5

    print("Test finished successfully...\n")


class LogWatch:
    """LogWatch class for watching log sources
    match -> (matchfield, operator, value, negated, caseinsens)
    matchfield -> one of (WHOLE, IP, SEVERITY, FACILITY, FIELD:range:sep, RE:regexp:field)
    """
    # TODO: Open file which has name of filename.
    def __init__(self, filename):
        self.rule_tree = None
        self.log_source_path = filename

    # TODO: Initiate the process.
    def run(self):
        pass

    # TODO: Receive and process log data from source then return.
    def readLog(self):
        pass

    # TODO: Parse given log according to RFC 5424.
    def parseLog(self):
        pass

    # Replace addressed Node with the given one.
    def setMatch(self, match, address = ()):
        if address == ():
            self.rule_tree = Node(match)
        else:
            node = self.rule_tree.getNode(address)
            node.value = match

    # Replace the the addressed node in the tree with a new node with given logical connector ("AND" or "OR").
    # Left branch of connector will be the previous node value, right branch will be the new match.
    def combineMatch(self, match, connector, address):
        node = self.rule_tree.getNode(address)
        temp = node.value
        node.value = connector
        node.left = Node(temp)
        node.right = Node(match)

    # Delete the node at given address, the sibling of the node will replace the parent logical operator.
    def delMatch(self, address):
        if address == ():  # deleting the rule_tree
            self.rule_tree = None
        else:
            parent_node = self.rule_tree.getNode(address[:-1])
            if address[-1] == 0:
                parent_node.value = parent_node.right.value
            else:
                parent_node.value = parent_node.left.value
            parent_node.right = None
            parent_node.left = None

    # Save current configuration as JSON to a file
    # Configuration -> log source path + rule tree
    def save(self, name):
        with open(name + ".json", "w") as write_file:
            data = {"log_source_path": self.log_source_path, "rule_tree": self.rule_tree}
            json.dump(data, write_file, indent = 2)

    # Load configuration from persistent storage - JSON file
    def load(self, name):
        with open(name + ".json", "r") as read_file:
            data = json.load(read_file)
            self.log_source_path = data["log_source_path"]
            self.rule_tree.fromJson(data["rule_tree"])


if __name__ == '__main__':
    main()
