"""Dummy XAP Client
"""
import json
import random
import gzip
import threading
import functools
from struct import Struct, pack, unpack
from collections import namedtuple
from enum import IntFlag, IntEnum
from platform import platform

RequestPacket = namedtuple('RequestPacket', 'token length data')
RequestStruct = Struct('<HB61s')

ResponsePacket = namedtuple('ResponsePacket', 'token flags length data')
ResponseStruct = Struct('<HBB60s')


def _gen_token():
    """Generate XAP token - cannot start with 00xx or 'reserved' (FFFE|FFFF)
    """
    token = random.randrange(0x0100, 0xFFFD)

    # swap endianness
    return unpack('<H', pack('>H', token))[0]


def _u32toBCD(val):  # noqa: N802
    """Create BCD string
    """
    return f'{val>>24}.{val>>16 & 0xFF}.{val & 0xFFFF}'


class XAPSecureStatus(IntEnum):
    LOCKED = 0x00
    UNLOCKING = 0x01
    UNLOCKED = 0x02


class XAPFlags(IntFlag):
    FAILURE = 0
    SUCCESS = 1 << 0
    SECURE_FAILURE = 1 << 1
    UNLOCK_IN_PROGRESS = 1 << 6
    UNLOCKED = 1 << 7


class XAPEventType(IntEnum):
    SECURE = 0x01
    KEYBOARD = 0x02
    USER = 0x03


class XAPDevice:
    def __init__(self, dev):
        """Constructor opens hid device and starts dependent services
        """
        self.responses = {}

        self.dev = hid.Device(path=dev['path'])

        self.bg = threading.Thread(target=self._read_loop, daemon=True)
        self.bg.start()

    def _read_loop(self):
        """Background thread to signal waiting transactions
        """
        while 1:
            array_alpha = self.dev.read(64, 100)
            if array_alpha:
                token = int.from_bytes(array_alpha[:2], 'little')
                event = self.responses.get(token)
                if event:
                    event._ret = array_alpha
                    event.set()

    def _query_device_info(self):
        datalen = int.from_bytes(self.transaction(b'\x01\x05') or bytes(0), 'little')
        if not datalen:
            return {}

        data = []
        offset = 0
        while offset < datalen:
            chunk = self.transaction(b'\x01\x06', offset)
            data += chunk
            offset += len(chunk)
        str_data = gzip.decompress(bytearray(data[:datalen]))
        return json.loads(str_data)

    def listen(self):
        """Receive a 'broadcast' message
        """
        token = 0xFFFF
        event = threading.Event()
        self.responses[token] = event

        event.wait()

        r = ResponsePacket._make(ResponseStruct.unpack(event._ret))
        return (r.flags, r.data[:r.length])

    def transaction(self, *args):
        """Request/Receive
        """
        # convert args to array of bytes
        data = bytes()
        for arg in args:
            if isinstance(arg, (bytes, bytearray)):
                data += arg
            if isinstance(arg, int):  # TODO: remove terrible assumption of u16
                data += arg.to_bytes(2, byteorder='little')

        token = _gen_token()

        p = RequestPacket(token, len(data), data)
        buffer = RequestStruct.pack(*list(p))

        event = threading.Event()
        self.responses[token] = event

        # prepend 0 on windows because reasons...
        if 'windows' in platform().lower():
            buffer = b'\x00' + buffer
        self.dev.write(buffer)

        event.wait(timeout=1)
        self.responses.pop(token, None)
        if not hasattr(event, '_ret'):
            return None

        r = ResponsePacket._make(ResponseStruct.unpack(event._ret))
        if r.flags != XAPFlags.SUCCESS:
            return None

        return r.data[:r.length]

    @functools.cache
    def version(self):
        ver = int.from_bytes(self.transaction(b'\x00\x00') or bytes(0), 'little')
        return {'xap': _u32toBCD(ver)}

    @functools.cache
    def info(self):
        data = self._query_device_info()
        data['_id'] = self.transaction(b'\x01\x08')
        data['xap'] = self.version()['xap']
        return data

    def status(self):
        lock = int.from_bytes(self.transaction(b'\x00\x03') or bytes(0), 'little')

        data = {}
        data['lock'] = XAPSecureStatus(lock).name
        return data

    def unlock(self):
        self.transaction(b'\x00\x04')

    def lock(self):
        self.transaction(b'\x00\x05')

    def reset(self):
        status = int.from_bytes(self.transaction(b'\x01\x07') or bytes(0), 'little')
        return status == 1


class XAPClient:
    @staticmethod
    def _lazy_imports():
        # Lazy load to avoid missing dependency issues
        global hid
        import hid

    @staticmethod
    def list(search=None):
        """Find compatible XAP devices
        """
        XAPClient._lazy_imports()

        def _is_xap_usage(x):
            return x['usage_page'] == 0xFF51 and x['usage'] == 0x0058

        def _is_filtered_device(x):
            name = '%04x:%04x' % (x['vendor_id'], x['product_id'])
            return name.lower().startswith(search.lower())

        devices = filter(_is_xap_usage, hid.enumerate())
        if search:
            devices = filter(_is_filtered_device, devices)

        return list(devices)

    def connect(self, dev):
        """Connect to a given XAP device
        """
        XAPClient._lazy_imports()

        return XAPDevice(dev)
