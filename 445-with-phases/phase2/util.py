#!/usr/bin/env python3


class AddressNotFoundError(Exception):
    pass


class NotAnObserverError(Exception):
    pass


class Node(dict):
    """Represents a binary tree node.
    """

    def __init__(self, value=None, left=None, right=None):
        super().__init__()
        self.__dict__ = self
        self.value = value
        self.left = left
        self.right = right

    # Return node at given address
    def getNode(self, address = ()):
        if address == ():
            return self
        else:
            tmp = self
            for step in address:
                if step == 0:
                    if tmp.left is not None:
                        tmp = tmp.left
                    else:
                        raise AddressNotFoundError("Could not find node at given address:", address)
                elif step == 1:
                    if tmp.right is not None:
                        tmp = tmp.right
                    else:
                        raise AddressNotFoundError("Could not find node at given address:", address)
                else:
                    raise AddressNotFoundError("Invalid address:", address)
            return tmp

    def load(self, dict_):
        if type(dict_["value"]) == list:
            self.value = tuple(dict_["value"])
        else:
            self.value = dict_["value"]
        if dict_["left"]:
            self.left = Node().load(dict_["left"])
        if dict_["right"]:
            self.right = Node().load(dict_["right"])
        return self


# TODO: This class may be a distinct script for the representation and simulation of client with Logwatcher
class Observer:
    """Represents an observer(user) of a Logwatch object
    """
    def __init__(self, watcher):
        self.filteredLogs = []
        watcher.register(self)

    def update(self, log):
        self.filteredLogs.append(log)