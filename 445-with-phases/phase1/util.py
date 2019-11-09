#!/usr/bin/env python3


class AddressNotFoundError(Exception):
    pass


class Node(dict):
    """Represents a binary tree node.
    """

    def __init__(self, value, left=None, right=None):
        super().__init__()
        self.__dict__ = self
        self.value = value
        self.left = left
        self.right = right

    # Alternative constructor method for Node to recover data from Json file
    def fromJson(self, dict_):
        root = Node(dict_['value'], dict_['left'], dict_['right'])
        root.left = Node.fromJson
        root.right = Node.fromJson
        return root

    # Return node at given address
    def getNode(self, address):
        if address == ():
            return self
        else:
            temp = self
            for step in address:
                if temp.left is not None and temp.right is not None:  # current node is not a leaf (i.e. rule)
                    if step == 0:
                        temp = temp.left
                    else:
                        temp = temp.right
                else:
                    raise AddressNotFoundError("Could not find node at given address:", address)

            return temp
