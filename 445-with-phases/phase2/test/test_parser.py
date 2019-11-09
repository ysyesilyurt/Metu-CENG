#!/usr/bin/env python3
import os
import sys
import unittest
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
from parser import Parser


class TestParser(unittest.TestCase):
    def test_parse(self):
        parserInstance = Parser()
        line = "Nov 20 00:10:00 john-pc gnome-shell[1758]: NOTE: Not using GLX TFP!"
        payload = parserInstance.parse(line, False)
        self.assertDictEqual({'timestamp': 1542661800, 'hostname': 'john-pc', 'appname': 'gnome-shell', 'pid': '1758',
                              'msg': 'NOTE: Not using GLX TFP!'}, payload)

        line = "<31>1 2003-10-11T22:14:15.003Z 8.850.22.32 su - ID47 - BOM'su root' failed for lonvick on /dev/pts/8"
        payload = parserInstance.parse(line, True)
        self.assertDictEqual({'severity': 'debug', 'facility': 'daemon', 'version': 1, 'timestamp': '2003-10-11T22:14:15.003Z',
                              'hostname': '8.850.22.32', 'appname': 'su', 'procid': None, 'msgid': 'ID47', 'sd': {},
                              'msg': "BOM'su root' failed for lonvick on /dev/pts/8"}, payload.as_dict())

def main():
    unittest.main(verbosity=3)


if __name__ == '__main__':
    main()
