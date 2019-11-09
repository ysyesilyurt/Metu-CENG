#!/usr/bin/env python3
import json
import os
import sys
import test_logWatch
import test_parser
import test_util
import unittest
testdir = os.path.dirname(__file__)
srcdir = '../'
sys.path.insert(0, os.path.abspath(os.path.join(testdir, srcdir)))
import watcher
import util


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
    # Step 1 - Loading rules
    logFile = "samples/sample.log"
    watcherInstance = watcher.LogWatch(logFile)
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
        sampleRules = util.Node().load(json.load(f)["rules"])
    assert sampleRules == watcherInstance.rules
    print("Rules are loaded successfully.", file=sys.stderr)

    # TODO: Run distinct test cases for parseSocket = False and parseSocket = True
    # Step 2 - Running Log Watcher
    watcherInstance.run()

    # Asserting if logs are filtered successfully
    with open("samples/sample_result") as f:
        result = f.read()
    assert str(watcherInstance.filteredLogs) == result
    print("Logs are filtered successfully.", file=sys.stderr)

    # Step 3 - Saving and loading
    watcherInstance.save("test_sample.json")
    watcherInstance2 = watcher.LogWatch()
    watcherInstance2.load("test_sample.json")
    os.remove("test_sample.json")

    # Asserting if rules are saved and loaded successfully
    assert watcherInstance.rules == watcherInstance2.rules
    print("Rules are saved and loaded successfully.", file=sys.stderr)


def main():
    runUnitTests()
    runIntegrationTests()
    print("\nAll tests are completed successfully.", file=sys.stderr)


if __name__ == '__main__':
    main()
