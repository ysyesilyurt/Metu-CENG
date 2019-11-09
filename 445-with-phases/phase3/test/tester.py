#!/usr/bin/env python3
import json
import os
import sqlite3
import sys
import unittest
import lwmanager
import util

testdir = os.path.dirname(__file__)
srcdir = '../'
sys.path.insert(0, os.path.abspath(os.path.join(testdir, srcdir)))


# Unit tests
def runUnitTests():
    suite = unittest.TestSuite()
    suite.addTests(unittest.defaultTestLoader.loadTestsFromModule(test_logWatch))
    suite.addTests(unittest.defaultTestLoader.loadTestsFromModule(test_parser))
    suite.addTests(unittest.defaultTestLoader.loadTestsFromModule(test_util))
    unittest.TextTestRunner(verbosity=3).run(suite)


# TODO: Extend test Integration test cases and sample logs/results etc.
# Integration tests
def runIntegrationTests():
    # Load database
    createTestDatabase()

    exit()

    logFile = "samples/sample.log"
    watcherInstance = watcher.LogWatch(0, None)
    watcherInstance.setMatch(("WHOLE", "EQ", "NOTE: Not using GLX TFP!", False, True))
    watcherInstance.combineMatch(("WHOLE", "RE", ".*Anacron.*", False, False), "OR")
    watcherInstance.combineMatch(("WHOLE", "RE", ".*anacron.*", False, False), "OR", (1,))
    watcherInstance.combineMatch(("WHOLE", "RE", ".*ERROR.*", False, True), "OR", (0,))
    watcherInstance.combineMatch(("WHOLE", "RE", ".*STREAM.*", False, True), "AND", (0, 1))
    watcherInstance.combineMatch(("WHOLE", "RE", ".*dhcp.*", False, True), "OR", (0, 0))
    watcherInstance.combineMatch(("WHOLE", "RE", ".*address.*", False, True), "AND", (0, 0, 1))
    watcherInstance.combineMatch(("WHOLE", "RE", ".*rfkill.*", False, True), "OR", (0, 0, 0))

    # Asserting if rules are loaded successfully
    with open("samples/sample_conf.json", "rb") as f:
        sampleRules = util.Node().loadJSON(json.load(f)["rules"])
    assert sampleRules == watcherInstance.rules
    print("Rules are created successfully.", file=sys.stderr)


def createTestDatabase():
    with sqlite3.connect("../db.sqlite3") as conn:
        c = conn.cursor()
        for i in range(3):
            c.execute("""insert into watcher_watchers(wid, name) values ({}, '{}');""".format(i, "Watcher {}".format(i)))

            for j in range(1, 8):
                c.execute("""insert into watcher_watcherrules(wid, rule_id, rule) values({}, {}, '{}')""".format(
                    i, j, ()))
                c.execute("""insert into watcher_watcherlogs(wid, log) values({}, '{}')""".format(i, "log{}".format(j)))


def main():
    # runUnitTests()
    runIntegrationTests()
    print("\nAll tests are completed successfully.", file=sys.stderr)


if __name__ == '__main__':
    main()
