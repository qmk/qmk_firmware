from intelhex import IntelHex
from cStringIO import StringIO


def sections(h):
    start, last_address = None, None
    for a in h.addresses():
        if last_address is None:
            start, last_address = a, a
            continue

        if a > last_address + 1:
            yield (start, last_address)
            start = a

        last_address = a

    if start:
        yield (start, last_address)


def print_sections(h):
    for s in sections(h):
        print "[0x%08X - 0x%08X]" % s


def decode(record):
    h = IntelHex()
    f = StringIO(record)
    h.loadhex(f)
    h.dump()
