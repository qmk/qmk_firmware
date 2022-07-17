"""XAP Device
"""
import hid
import json
import time
import gzip
import random
import threading
import functools
from struct import Struct, pack, unpack
from collections import namedtuple
from platform import platform

from .types import XAPSecureStatus, XAPFlags, XAPRouteError
from .routes import XAPRoutes
from .util import u32toBCD

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


class XAPDevice:
    def __init__(self, dev):
        """Constructor opens hid device and starts dependent services
        """
        self.responses = {}
        self.do_read = True

        self.dev = hid.Device(path=dev['path'])

        self.bg = threading.Thread(target=self._read_loop, daemon=True)
        self.bg.start()

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, exc_traceback):
        self.close()

    def close(self):
        self.do_read = False
        time.sleep(1)
        self.dev.close()

    def _read_loop(self):
        """Background thread to signal waiting transactions
        """
        while self.do_read:
            array_alpha = self.dev.read(ResponseStruct.size, 100)
            if array_alpha:
                token = int.from_bytes(array_alpha[:2], 'little')
                event = self.responses.get(token)
                if event:
                    event._ret = array_alpha
                    event.set()

    def _query_device_info(self):
        datalen = int.from_bytes(self.transaction(XAPRoutes.QMK_CONFIG_BLOB_LEN) or bytes(0), 'little')
        if not datalen:
            return {}

        data = []
        offset = 0
        while offset < datalen:
            chunk = self.transaction(XAPRoutes.QMK_CONFIG_BLOB_CHUNK, offset)
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

        while not hasattr(event, '_ret'):
            event.wait(timeout=0.25)

        r = ResponsePacket._make(ResponseStruct.unpack(event._ret))
        return (r.flags, r.data[:r.length])

    def _transaction(self, *args):
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
        if r.flags & XAPFlags.SUCCESS == 0:
            return None

        return r.data[:r.length]

    @functools.lru_cache
    def capability(self, route):
        cap = int.from_bytes(self._transaction(route) or bytes(0), 'little')
        return cap

    @functools.lru_cache
    def subsystem(self):
        sub = int.from_bytes(self._transaction(XAPRoutes.XAP_SUBSYSTEM_QUERY) or bytes(0), 'little')
        return sub

    @functools.lru_cache
    def version(self):
        xap = int.from_bytes(self._transaction(XAPRoutes.XAP_VERSION_QUERY) or bytes(0), 'little')
        qmk = int.from_bytes(self._transaction(XAPRoutes.QMK_VERSION_QUERY) or bytes(0), 'little')
        return {'xap': u32toBCD(xap), 'qmk': u32toBCD(qmk)}

    def _ensure_route(self, route):
        (sub, rt) = route
        cap = bytes([sub, 1])

        if self.subsystem() & (1 << sub) == 0:
            raise XAPRouteError("subsystem not available")
        if self.capability(cap) & (1 << rt) == 0:
            raise XAPRouteError("route not available")

    def transaction(self, route, *args):
        self._ensure_route(route)

        return self._transaction(route, *args)

    @functools.lru_cache
    def info(self):
        data = self._query_device_info()
        data['_id'] = self.transaction(XAPRoutes.QMK_HARDWARE_ID)
        data['_version'] = self.version()
        return data

    def status(self):
        lock = int.from_bytes(self.transaction(XAPRoutes.XAP_SECURE_STATUS) or bytes(0), 'little')

        data = {}
        data['lock'] = XAPSecureStatus(lock).name
        return data

    def unlock(self):
        self.transaction(XAPRoutes.XAP_SECURE_UNLOCK)

    def lock(self):
        self.transaction(XAPRoutes.XAP_SECURE_LOCK)

    def reset(self):
        status = int.from_bytes(self.transaction(XAPRoutes.QMK_BOOTLOADER_JUMP) or bytes(0), 'little')
        return status == 1
