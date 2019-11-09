#!/usr/bin/env python3
import os
import sys
import unittest
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "../old")))
from util import Node
from watcher import LogWatch


class TestNode(unittest.TestCase):
    def test_getNode(self):
        watcherInstance = LogWatch(0, None)
        watcherInstance.rules = Node(())
        watcherInstance.rules.left = Node((0,))
        watcherInstance.rules.right = Node((1,))
        watcherInstance.rules.left.left = Node((0, 0))
        watcherInstance.rules.left.right = Node((0, 1))
        watcherInstance.rules.right.left = Node((1, 0))
        watcherInstance.rules.right.right = Node((1, 1))
        self.assertEqual(watcherInstance.rules, watcherInstance.rules.getNode())
        self.assertEqual(watcherInstance.rules.left, watcherInstance.rules.getNode((0,)))
        self.assertEqual(watcherInstance.rules.right, watcherInstance.rules.getNode((1,)))
        self.assertEqual(watcherInstance.rules.left.left, watcherInstance.rules.getNode((0, 0)))
        self.assertEqual(watcherInstance.rules.left.right, watcherInstance.rules.getNode((0, 1)))
        self.assertEqual(watcherInstance.rules.right.left, watcherInstance.rules.getNode((1, 0)))
        self.assertEqual(watcherInstance.rules.right.right, watcherInstance.rules.getNode((1, 1)))

    def test_dump(self):
        watcherInstance = LogWatch(0, None)
        watcherInstance.rules = Node(())
        watcherInstance.rules.left = Node((0,))
        watcherInstance.rules.right = Node((1,))
        watcherInstance.rules.left.left = Node((0, 0))
        watcherInstance.rules.left.right = Node((0, 1))
        watcherInstance.rules.right.left = Node((1, 0))
        watcherInstance.rules.right.right = Node((1, 1))
        dump = watcherInstance.rules.dump()
        self.assertEqual((((), ()), ((0,), (0,)), ((0, 0), (0, 0)), ((0, 1), (0, 1)), ((1,), (1,)), ((1, 0), (1, 0)), ((1, 1), (1, 1))), dump)

    def test_load(self):
        rules1 = Node(())
        rules1.left = Node((0, ))
        rules1.left.left = Node((0, 0))
        rules1.left.right = Node((0, 1))
        rules1.right = Node((1, ))
        rules1.right.left = Node((1, 0))
        rules1.right.right = Node((1, 1))

        rules2 = Node()
        rules2.load([('()', '()'), ('(0,)', '(0,)'), ('(0, 0)', '(0, 0)'), ('(0, 1)', '(0, 1)'), ('(1,)', '(1,)'),
                     ('(1, 0)', '(1, 0)'), ('(1, 1)', '(1, 1)')])
        self.assertEqual(rules1, rules2)
