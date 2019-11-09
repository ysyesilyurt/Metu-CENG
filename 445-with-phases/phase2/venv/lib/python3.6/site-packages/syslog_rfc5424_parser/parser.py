from pyparsing import Optional, Literal, QuotedString, Word, ZeroOrMore, OneOrMore, White, Group, Combine, Suppress
from pyparsing import nums, printables, restOfLine, lineEnd

NameAscii = ''.join(c for c in printables if c not in ("=", " ", "]", '"'))
NilValue = "-"
SP = Suppress(White(ws=' ', min=1, max=1))


def toInt(s, loc, toks):
    return int(toks[0])


def maybeToInt(s, loc, toks):
    if all(x.isdigit() for x in toks[0]):
        return int(toks[0])
    else:
        return toks[0]


pri = Combine(Suppress(Literal("<")) + Word(nums, min=1, max=3) + Suppress(Literal(">"))).setParseAction(toInt)
version = Word(nums).setParseAction(toInt)
dash = Literal("-")
colon = Literal(":")
rfc3164_date = Word(nums, min=4, max=4) + dash + Word(nums, min=2, max=2) + dash + Word(nums, min=2, max=2)
rfc3164_time = Word(nums, min=2, max=2) + colon + Word(nums, min=2, max=2) + colon + Word(nums, min=2, max=2) + \
    Optional(Literal(".") + Word(nums, min=1, max=6))
rfc3164_timenumoffset = (Literal("-") | Literal("+")) + Word(nums, min=2, max=2) + colon + Word(nums, min=2, max=2)
rfc3164_timeoffset = Literal("Z") | rfc3164_timenumoffset
rfc3164_timestamp = Combine(rfc3164_date + Literal("T") + rfc3164_time + rfc3164_timeoffset)

timestamp = NilValue | rfc3164_timestamp
hostname = NilValue | Word(printables, min=1, max=255)
appname = NilValue | Word(printables, min=1, max=48)
procname = NilValue | Word(printables, min=1, max=128).setParseAction(maybeToInt)
msgid = NilValue | Word(printables, min=1, max=32)

header = Group(
    pri.setResultsName('pri') + version.setResultsName('version') + SP +
    timestamp.setResultsName('timestamp') + SP + hostname.setResultsName('hostname') + SP +
    appname.setResultsName('appname') + SP + procname.setResultsName('procname') + SP +
    msgid.setResultsName('msgid')
)

sd_name = Word(NameAscii, min=1, max=32)
sd_id = sd_name
param_name = sd_name
sd_param = Group(
    param_name.setResultsName('param_name') + Suppress(Literal("=")) +
    QuotedString(quoteChar='"', escChar='\\', escQuote='\\').setResultsName('param_value')
)

sd_element = Group(
    Suppress("[") + sd_id.setResultsName('sd_id') + ZeroOrMore(SP + sd_param).setResultsName('sd_params') +
    Suppress("]")
)

structured_data = (NilValue | Group(OneOrMore(sd_element))).setResultsName('sd_element')

msg = Combine(restOfLine + lineEnd)

syslog_message = header.setResultsName('header') + SP + structured_data.setResultsName('sd') + \
    Optional(SP + msg.setResultsName('msg'))


__all__ = ['syslog_message', 'structured_data', 'header']
