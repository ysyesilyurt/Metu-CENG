#!/usr/bin/env python3
import os
import sys
import unittest
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
from util import Node
from watcher import LogWatch


class TestNode(unittest.TestCase):
    def test_getNode(self):
        watcherInstance = LogWatch()
        watcherInstance.rules = Node("()")
        watcherInstance.rules.left = Node("(0)")
        watcherInstance.rules.right = Node("(1)")
        watcherInstance.rules.left.left = Node("(0, 0)")
        watcherInstance.rules.left.right = Node("(0, 1)")
        watcherInstance.rules.right.left = Node("(1, 0)")
        watcherInstance.rules.right.right = Node("(1, 1)")
        self.assertEqual(watcherInstance.rules, watcherInstance.rules.getNode())
        self.assertEqual(watcherInstance.rules.left, watcherInstance.rules.getNode((0,)))
        self.assertEqual(watcherInstance.rules.right, watcherInstance.rules.getNode((1,)))
        self.assertEqual(watcherInstance.rules.left.left, watcherInstance.rules.getNode((0, 0)))
        self.assertEqual(watcherInstance.rules.left.right, watcherInstance.rules.getNode((0, 1)))
        self.assertEqual(watcherInstance.rules.right.left, watcherInstance.rules.getNode((1, 0)))
        self.assertEqual(watcherInstance.rules.right.right, watcherInstance.rules.getNode((1, 1)))


# TODO: Add test cases for Observers with their own operations
