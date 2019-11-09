import time

import pyparsing

from . import parser
from .constants import SyslogSeverity, SyslogFacility


class ParseError(Exception):
    def __init__(self, description, message):
        self.description = description
        self.message = message

    def __repr__(self):
        return '{0}({1!r}, {2!r})'.format(self.__class__.__name__, self.description, self.message)  # pragma: no cover

    def __str__(self):
        return '{0}: {1!r}'.format(self.description, self.message)  # pragma: no cover


class SyslogMessage(object):
    """Representation of a single RFC5424-format syslog message. """

    __slots__ = ['severity', 'facility', 'version', 'timestamp', 'hostname', 'appname', 'procid', 'msgid', 'sd', 'msg']

    def __init__(self, severity, facility, version=1, timestamp='-', hostname='-', appname='-', procid=None,
                 msgid=None, sd='-', msg=None):
        """Initialize a syslog message (defaults correspond to the minimal default in the RFC"""
        # I wish Python had initializer lists
        self.severity = severity
        self.facility = facility
        self.version = version
        self.timestamp = timestamp
        self.hostname = hostname
        self.appname = appname
        self.procid = procid
        self.msgid = msgid
        if sd == '-':
            self.sd = {}
        else:
            self.sd = sd
        self.msg = msg

    def __str__(self):
        """Return this object represented as appropriate for the wire"""
        if self.facility == SyslogFacility.unknown:
            raise ValueError('Cannot dump a SyslogMessage with unknown facility')
        pri = int(self.facility) * 8 + int(self.severity)
        if isinstance(self.timestamp, (int, float)):
            timestamp = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime(self.timestamp))
        else:
            timestamp = self.timestamp
        sd = []
        for sd_id, sd_params in self.sd.items():
            sd_data = []
            for k, v in sd_params.items():
                sd_data.append(' {k}="{v}"'.format(k=k, v=v))
            sd.append('[{sd_id}{sd_data}]'.format(sd_id=sd_id, sd_data=''.join(sd_data)))
        if sd:
            sd = ''.join(sd)
        else:
            sd = '-'
        if self.msg:
            rest = ' {msg}'.format(msg=self.msg)
        else:
            rest = ''
        return '<{pri}>{version} {timestamp} {hostname} {appname} {procid} {msgid} {sd}{rest}'.format(
            pri=pri, version=self.version, timestamp=timestamp, hostname=self.hostname,
            appname=self.appname, procid='-' if self.procid is None else self.procid,
            msgid='-' if self.msgid is None else self.msgid,
            sd=sd, rest=rest
        )

    @classmethod
    def parse(cls, message_string):
        """Construct a syslog message from a string"""
        try:
            groups = parser.syslog_message.parseString(message_string)
        except pyparsing.ParseException:
            raise ParseError('Unable to parse message', message_string)
        header = groups['header']
        structured_data = groups['sd']
        if 'msg' in groups:
            msg = groups['msg']
        else:
            msg = None
        pri = int(header['pri'])
        fac = pri >> 3
        sev = pri & 7
        severity = SyslogSeverity(sev)
        try:
            facility = SyslogFacility(fac)
        except Exception:
            facility = SyslogFacility.unknown
        version = header['version']
        hostname = header['hostname']
        timestamp = header['timestamp']
        appname = header['appname']
        procid = header['procname']
        if procid == '-':
            procid = None
        msgid = header['msgid']
        if msgid == '-':
            msgid = None
        msg = msg
        sd = {}
        """StructuredData pairs from the message, represented as a dictionary"""
        if structured_data != '-':
            for item in structured_data:
                sd.setdefault(item['sd_id'], {})
                if 'sd_params' in item:
                    for param_pair in item['sd_params']:
                        sd[item['sd_id']][param_pair['param_name']] = param_pair.get('param_value', '')
        return cls(severity=severity, facility=facility, version=version, hostname=hostname,
                   timestamp=timestamp, appname=appname, procid=procid, msgid=msgid, msg=msg,
                   sd=sd)

    def __repr__(self):
        return '{0}({1})'.format(
            self.__class__.__name__,
            ','.join('{0}={1!r}'.format(k, getattr(self, k)) for k in self.__slots__)
        )

    def as_dict(self):
        """Dump this class to a dictionary of primitive objects, suitable for serializing with JSON/MsgPack/etc."""

        return dict(
            (k, getattr(self, k).name if k in ('severity', 'facility') else getattr(self, k))
            for k in self.__slots__
        )
