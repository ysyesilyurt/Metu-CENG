#!/usr/bin/env python3
import os
import sys
import unittest
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
import watcher
from util import Node


class TestLogWatch(unittest.TestCase):
    def test_applyRule(self):
        watcherInstance = watcher.LogWatch()

        # Case 1 - matchfield : WHOLE
        payload = {'timestamp': 1542661800, 'hostname': 'john-pc', 'appname': 'gnome-shell', 'pid': '1758',
                              'msg': 'NOTE: Not using GLX TFP!'}
        self.assertTrue(watcherInstance.applyRule(("WHOLE", "EQ", "NOTE: Not using GLX TFP!", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("WHOLE", "EQ", "NOTE: Not using GLX TFP!", False, True), payload))
        self.assertTrue(watcherInstance.applyRule(("WHOLE", "EQ", "note: not using glx tfp!", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("WHOLE", "EQ", "note: not using glx tfp!", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("WHOLE", "EQ", "note: not using glx tfp!", True, False), payload))
        self.assertTrue(watcherInstance.applyRule(("WHOLE", "EQ", "note: not using glx tfp!", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("WHOLE", "RE", ".*GLX.*", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("WHOLE", "RE", ".*GLX.*", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("WHOLE", "RE", ".*GLX.*", True, False), payload))
        self.assertFalse(watcherInstance.applyRule(("WHOLE", "RE", ".*GLX.*", True, True), payload))
        self.assertTrue(watcherInstance.applyRule(("WHOLE", "RE", ".*tfp!", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("WHOLE", "RE", ".*tfp!", False, False), payload))

        # Case 2 - matchfield : IP
        self.assertTrue(watcherInstance.applyRule(("IP", "EQ", "john-pc", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "EQ", "John-Pc", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("IP", "EQ", "John-Pc", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "EQ", "john-pc", True, False), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "EQ", "John-Pc", True, True), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "EQ", "176.240.43.210", False, False), payload))

        self.assertTrue(watcherInstance.applyRule(("IP", "RE", ".*john-pc.*", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "RE", ".*John-Pc.*", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("IP", "RE", ".*John-Pc.*", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "RE", ".*john-pc.*", True, False), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "RE", ".*John-Pc.*", True, True), payload))

        payload = {'timestamp': 1542661800, 'hostname': "176.240.43.210", 'appname': 'gnome-shell', 'pid': '1758',
                    'msg': 'NOTE: Not using GLX TFP!'}
        self.assertTrue(watcherInstance.applyRule(("IP", "EQ", "176.240.43.210", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "EQ", "192.168.14.7", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "EQ", "176.240.43.210", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("IP", "LT", "157.51.14.41", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "LT", "192.168.14.7", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "LT", "157.51.14.41", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("IP", "GT", "192.168.14.7", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "GT", "157.51.14.41", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "GT", "192.168.14.7", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("IP", "LE", "176.240.43.210", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("IP", "LE", "157.51.14.41", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "LE", "192.168.14.7", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "LE", "176.240.43.210", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("IP", "GE", "176.240.43.210", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("IP", "GE", "192.168.14.7", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "GE", "157.51.14.41", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("IP", "GE", "176.240.43.210", True, False), payload))

        # Case 3 - matchfield : SEVERITY
        payload = {'severity': 'crit', 'facility': 'auth', 'version': 1, 'timestamp': '2003-10-11T22:14:15.003Z',
                   'hostname': '193.156.21.2', 'appname': 'su', 'procid': None, 'msgid': 'ID47', 'sd': {},
                   'msg': "BOM'su root' failed for lonvick on /dev/pts/8"}

        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "EQ", "crit", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "EQ", 5, False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("SEVERITY", "EQ", "criT", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "EQ", "criT", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("SEVERITY", "EQ", "crit", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "LT", "debug", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "LT", 0, False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("SEVERITY", "LT", "emerg", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("SEVERITY", "LT", "debuG", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "LT", "debuG", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("SEVERITY", "LT", "debug", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "GT", "emerg", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "GT", 7, False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("SEVERITY", "GT", "debug", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("SEVERITY", "GT", "emerG", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "GT", "emerG", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("SEVERITY", "GT", "emerg", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "LE", "crit", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "LE", 5, False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "LE", "debug", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("SEVERITY", "LE", "emerg", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("SEVERITY", "LE", "criT", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "LE", "criT", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("SEVERITY", "LE", "crit", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "GE", "crit", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "GE", 5, False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "GE", "emerg", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("SEVERITY", "GE", "debug", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("SEVERITY", "GE", "criT", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("SEVERITY", "GE", "criT", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("SEVERITY", "GE", "crit", True, False), payload))



        # Case 4 - matchfield : FACILITY
        self.assertTrue(watcherInstance.applyRule(("FACILITY", "EQ", "auth", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FACILITY", "EQ", 19, False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("FACILITY", "EQ", "autH", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FACILITY", "EQ", "autH", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("FACILITY", "EQ", "auth", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("FACILITY", "LT", "ntp", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FACILITY", "LT", 11, False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FACILITY", "LT", "unknown", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("FACILITY", "LT", "kern", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("FACILITY", "LT", "ntP", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FACILITY", "LT", "ntP", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("FACILITY", "LT", "ntp", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("FACILITY", "GT", "kern", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FACILITY", "GT", 23, False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("FACILITY", "GT", "unknown", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("FACILITY", "GT", "ntp", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("FACILITY", "GT", "kerN", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FACILITY", "GT", "kerN", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("FACILITY", "GT", "kern", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("FACILITY", "LE", "auth", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FACILITY", "LE", 19, False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FACILITY", "LE", "ntp", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("FACILITY", "LE", "kern", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("FACILITY", "LE", "autH", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FACILITY", "LE", "autH", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("FACILITY", "LE", "auth", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("FACILITY", "GE", "auth", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FACILITY", "GE", 19, False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FACILITY", "GE", "kern", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("FACILITY", "GE", "ntp", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("FACILITY", "LE", "autH", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FACILITY", "LE", "autH", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("FACILITY", "LE", "auth", True, False), payload))

        # Case 5 - matchfield : FIELD
        payload = {'severity': 'crit', 'facility': 'auth', 'version': 1, 'timestamp': '2003-10-11T22:14:15.003Z',
                   'hostname': '193.156.21.2', 'appname': 'su', 'procid': None, 'msgid': 'ID47', 'sd': {},
                   'msg': "BOM,'su root',failed,for,lonvick,on,/dev/pts/8,check"}

        self.assertTrue(watcherInstance.applyRule(("FIELD:7:,", "EQ", "check", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FIELD:2:,", "EQ", "failed", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FIELD:2-5:,", "EQ", "failed,for,lonvick,on", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("FIELD:2-5:,", "EQ", "Failed,For,Lonvick,On", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FIELD:2-5:,", "EQ", "Failed,For,Lonvick,On", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("FIELD:2-5:,", "EQ", "failed,for,lonvick,on", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("FIELD:7:,", "RE", ".*check.*", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FIELD:2:,", "RE", ".*failed.*", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FIELD:2-5:,", "RE", ".*failed,for,lonvick,on.*", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("FIELD:2-5:,", "RE", ".*Failed,For,Lonvick,On.*", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FIELD:2-5:,", "RE", ".*Failed,For,Lonvick,On.*", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("FIELD:2-5:,", "RE", ".*failed,for,lonvick,on.*", True, False), payload))

        payload = {'severity': 'crit', 'facility': 'auth', 'version': 1, 'timestamp': '2003-10-11T22:14:15.003Z',
                   'hostname': '193.156.21.2', 'appname': 'su', 'procid': None, 'msgid': 'ID47', 'sd': {},
                   'msg': "BOM 'grep' failed for lonvick on /dev/pts/8 check"}

        self.assertTrue(watcherInstance.applyRule(("FIELD:7: ", "EQ", "check", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FIELD:2: ", "EQ", "failed", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FIELD:2-5: ", "EQ", "failed for lonvick on", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("FIELD:2-5: ", "EQ", "Failed For Lonvick On", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FIELD:2-5: ", "EQ", "Failed For Lonvick On", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("FIELD:2-5: ", "EQ", "failed for lonvick on", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("FIELD:7: ", "RE", ".*check.*", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FIELD:2: ", "RE", ".*failed.*", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FIELD:2-5: ", "RE", ".*failed for lonvick on.*", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("FIELD:2-5: ", "RE", ".*Failed For Lonvick On.*", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("FIELD:2-5: ", "RE", ".*Failed For Lonvick On.*", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("FIELD:2-5: ", "RE", ".*failed for lonvick on.*", True, False), payload))

        # Case 6 - matchfield : RE
        payload = {'severity': 'crit', 'facility': 'auth', 'version': 1, 'timestamp': '2003-10-11T22:14:15.003Z',
                   'hostname': '193.156.21.2', 'appname': 'su', 'procid': None, 'msgid': 'ID47', 'sd': {},
                   'msg': "BOM'su root' failed for lonvick on /dev/pts/8"}

        self.assertTrue(watcherInstance.applyRule(("RE:.*su root.* (?P<event>.*ed).*on (?P<event_location>.+):event_location", "EQ", "/dev/pts/8", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("RE:.*su root.* (?P<event>.*ed).*on (?P<event_location>.+):event", "EQ", "failed", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("RE:.*su root.* (?P<event>.*ed).*on (?P<event_location>.+):event", "EQ", "faileD", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("RE:.*su root.* (?P<event>.*ed).*on (?P<event_location>.+):event", "EQ", "faileD", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("RE:.*su root.* (?P<event>.*ed).*on (?P<event_location>.+):event", "EQ", "failed", True, False), payload))

        self.assertTrue(watcherInstance.applyRule(("RE:.*su root.* (?P<event>.*ed).*on (?P<event_location>.+):event_location","RE", ".*dev.*", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("RE:.*su root.* (?P<event>.*ed).*on (?P<event_location>.+):event", "RE", ".*fail.*", False, False), payload))
        self.assertFalse(watcherInstance.applyRule(("RE:.*su root.* (?P<event>.*ed).*on (?P<event_location>.+):event", "RE", ".*faiL.*", False, False), payload))
        self.assertTrue(watcherInstance.applyRule(("RE:.*su root.* (?P<event>.*ed).*on (?P<event_location>.+):event", "RE", ".*faiL.*", False, True), payload))
        self.assertFalse(watcherInstance.applyRule(("RE:.*su root.* (?P<event>.*ed).*on (?P<event_location>.+):event", "RE", ".*fail.*", True, False), payload))

    def test_combineMatch(self):
        # Case 1 - Single element rule tree
        watcherInstance = watcher.LogWatch()
        watcherInstance.rules.value = "OLD_MATCH"
        watcherInstance.combineMatch("NEW_MATCH", "AND")
        self.assertDictEqual({"value": "AND", "left": {"value": "OLD_MATCH", "left": None, "right": None},
                              "right": {"value": "NEW_MATCH", "left": None, "right": None}}, watcherInstance.rules)

        # Case 2 - Leaf of rule tree
        watcherInstance.rules.value = "AND"
        watcherInstance.rules.left = Node("OLD_MATCH")
        watcherInstance.rules.right = Node("SOME_MATCH")
        watcherInstance.combineMatch("NEW_MATCH", "OR", (0,))
        self.assertDictEqual({"value": "AND",
                              "left": {"value": "OR", "left": {"value": "OLD_MATCH", "left": None, "right": None},
                                       "right": {"value": "NEW_MATCH", "left": None, "right": None}},
                              "right": {"value": "SOME_MATCH", "left": None, "right": None}}, watcherInstance.rules)

    def test_delMatch(self):
        # Case 1 - Single element of rule tree
        watcherInstance = watcher.LogWatch()
        watcherInstance.rules.value = "MATCH"
        watcherInstance.delMatch()
        self.assertDictEqual({"value": None, "left": None, "right": None}, watcherInstance.rules)

        # Case 2 - Internal element of rule tree
        watcherInstance = watcher.LogWatch()
        watcherInstance.rules.value = "AND"
        watcherInstance.rules.left = Node("LEFT_MATCH")
        watcherInstance.rules.right = Node("RIGHT_MATCH")
        watcherInstance.delMatch((0,))
        self.assertDictEqual({"value": "RIGHT_MATCH", "left": None, "right": None}, watcherInstance.rules)

    def test_setMatch(self):
        # Case 1 - Empty rules
        watcherInstance = watcher.LogWatch()
        watcherInstance.setMatch("MATCH")
        self.assertDictEqual({"value": "MATCH", "left": None, "right": None}, watcherInstance.rules)

        # Case 2 - Single element of rule tree
        watcherInstance = watcher.LogWatch()
        watcherInstance.rules.value = "OLD_MATCH"
        watcherInstance.setMatch("NEW_MATCH")
        self.assertDictEqual({"value": "NEW_MATCH", "left": None, "right": None}, watcherInstance.rules)

        # Case 3 - Leaf of rule tree
        watcherInstance = watcher.LogWatch()
        watcherInstance.rules.value = "AND"
        watcherInstance.rules.left = Node("OLD_LEFT_MATCH")
        watcherInstance.rules.right = Node("OLD_RIGHT_MATCH")
        watcherInstance.setMatch("NEW_LEFT_MATCH", (0,))
        watcherInstance.setMatch("NEW_RIGHT_MATCH", (1,))
        self.assertDictEqual({"value": "AND", "left": {"value": "NEW_LEFT_MATCH", "left": None, "right": None},
                              "right": {"value": "NEW_RIGHT_MATCH", "left": None, "right": None}},
                             watcherInstance.rules)

    def test_save(self):
        watcherInstance = watcher.LogWatch("TEST_LOG_FILE")
        watcherInstance.rules = Node("()")
        watcherInstance.rules.left = Node("(0)")
        watcherInstance.rules.right = Node("(1)")
        watcherInstance.rules.left.left = Node("(0, 0)")
        watcherInstance.rules.left.right = Node("(0, 1)")
        watcherInstance.rules.right.left = Node("(1, 0)")
        watcherInstance.rules.right.right = Node("(1, 1)")
        watcherInstance.save("test_sample.json")

        with open("samples/test_sample.json") as f:
            expected = f.read()
        with open("test_sample.json") as f:
            actual = f.read()
        self.assertEqual(expected, actual)
        os.remove("test_sample.json")

    def test_load(self):
        watcherInstance = watcher.LogWatch("TEST_LOG_FILE")
        watcherInstance.rules = Node("()")
        watcherInstance.rules.left = Node("(0)")
        watcherInstance.rules.right = Node("(1)")
        watcherInstance.rules.left.left = Node("(0, 0)")
        watcherInstance.rules.left.right = Node("(0, 1)")
        watcherInstance.rules.right.left = Node("(1, 0)")
        watcherInstance.rules.right.right = Node("(1, 1)")

        watcherInstance2 = watcher.LogWatch()
        watcherInstance2.load("samples/test_sample.json")
        self.assertEqual(watcherInstance.rules, watcherInstance2.rules)


def main():
    unittest.main(verbosity=3)


if __name__ == '__main__':
    main()
