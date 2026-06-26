# Copyright 2022 QMK
# SPDX-License-Identifier: GPL-2.0-or-later
import json
import time
import gzip
import random
import threading
import functools
from typing import Optional
from struct import pack, unpack
from platform import platform

from .types import XAPSecureStatus, XAPFlags, XAPRequest, XAPResponse, XAPBroadcast
from .routes import XAPRoutes, XAPRouteError


def _u32_to_bcd(val: bytes) -> str:  # noqa: N802
    """Create BCD string
    """
    tmp = "{:08x}".format(val)
    major = int(tmp[0:2])
    minor = int(tmp[2:4])
    patch = int(tmp[4:8])

    return f'{major}.{minor}.{patch}'


def _gen_token() -> bytes:
    """Generate XAP token - cannot start with 00xx or 'reserved' (FFFE|FFFF)
    """
    token = random.randrange(0x0100, 0xFFFD)

    # swap endianness
    return unpack('<H', pack('>H', token))[0]


class XAPDeviceBase:
    """Raw XAP interactions
    """
    def __init__(self, dev: dict, timeout: int = 1.0):
        """Constructor opens hid device and starts dependent services
        """
        self.responses = {}
        self.timeout = timeout
        self.running = True

        # lazy import to avoid compile issues
        import hid

        self.dev = hid.Device(path=dev['path'])

        self.bg = threading.Thread(target=self._read_loop, daemon=True)
        self.bg.start()

    def close(self):
        """Close device and stop dependent services
        """
        self.running = False
        time.sleep(1)
        self.dev.close()

    def _read_loop(self):
        """Background thread to signal waiting transactions
        """
        while self.running:
            data = self.dev.read(XAPResponse.fmt.size, 100)
            if data:
                r = XAPResponse.from_bytes(data)
                event = self.responses.get(r.token)
                if event:
                    event._ret = data
                    event.set()

    def transaction(self, *args) -> Optional[bytes]:
        """Request/Receive Helper
        """
        # convert args to array of bytes
        data = bytes()
        for arg in args:
            if isinstance(arg, (bytes, bytearray)):
                data += arg
            if isinstance(arg, int):  # TODO: remove terrible assumption of u16
                data += arg.to_bytes(2, byteorder='little')

        token = _gen_token()

        buffer = XAPRequest(token, len(data), data).to_bytes()

        event = threading.Event()
        self.responses[token] = event

        # prepend 0 on windows because reasons...
        if 'windows' in platform().lower():
            buffer = b'\x00' + buffer
        self.dev.write(buffer)

        event.wait(timeout=self.timeout)
        self.responses.pop(token, None)
        if not hasattr(event, '_ret'):
            return None

        r = XAPResponse.from_bytes(event._ret)
        if r.flags & XAPFlags.SUCCESS == 0:
            return None

        return r.data[:r.length]

    def listen(self) -> dict:
        """Receive a single 'broadcast' message
        """
        token = 0xFFFF
        event = threading.Event()
        self.responses[token] = event

        # emulate a blocking read while allowing `ctrl+c` on windows
        while not hasattr(event, '_ret'):
            event.wait(timeout=0.25)

        r = XAPBroadcast.from_bytes(event._ret)
        return (r.event, r.data[:r.length])


class XAPDevice(XAPDeviceBase):
    """XAP device interaction
    """
    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, exc_traceback):
        self.close()

    def _query_device_info(self) -> dict:
        """Helper to reconstruct info.json from requested chunks
        """
        datalen = self.int_transaction(XAPRoutes.QMK_CONFIG_BLOB_LEN)
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

    def _ensure_route(self, route: bytes):
        """Check a route can be accessed

        Raises:
            XAPRouteError: Access to invalid route attempted
        """
        # TODO: Remove assumption that capability is always xx01
        (remain, sub, rt) = (route[:-2], route[-2], route[-1])
        cap = remain + bytes([sub, 1])

        # recurse for nested routes
        if remain:
            self._ensure_route(remain + bytes([sub]))

        if self.subsystems() & (1 << sub) == 0:
            raise XAPRouteError("subsystem not available")
        if self.capability(cap) & (1 << rt) == 0:
            raise XAPRouteError("route not available")

    def transaction(self, route: bytes, *args):
        """Request/Receive to XAP device

        Raises:
            XAPRouteError: Access to invalid route attempted
        """
        self._ensure_route(route)

        return super().transaction(route, *args)

    def int_transaction(self, route: bytes, *args):
        """transaction with int parsing
        """
        return int.from_bytes(self.transaction(route, *args) or bytes(0), 'little')

    @functools.lru_cache
    def capability(self, route: bytes):
        # use parent transaction as we want to ignore capability checks
        return int.from_bytes(super().transaction(route) or bytes(0), 'little')

    @functools.lru_cache
    def subsystems(self):
        # use parent transaction as we want to ignore capability checks
        return int.from_bytes(super().transaction(XAPRoutes.XAP_SUBSYSTEM_QUERY) or bytes(0), 'little')

    @functools.lru_cache
    def version(self) -> dict:
        """Query version data from device
        """
        xap = self.int_transaction(XAPRoutes.XAP_VERSION_QUERY)
        qmk = self.int_transaction(XAPRoutes.QMK_VERSION_QUERY)
        return {'xap': _u32_to_bcd(xap), 'qmk': _u32_to_bcd(qmk)}

    @functools.lru_cache
    def info(self) -> dict:
        """Query config data from device
        """
        data = self._query_device_info()
        data['_id'] = self.transaction(XAPRoutes.QMK_HARDWARE_ID)
        data['_version'] = self.version()
        return data

    def status(self) -> dict:
        """Query current device state
        """
        lock = self.int_transaction(XAPRoutes.XAP_SECURE_STATUS)

        data = {}
        data['lock'] = XAPSecureStatus(lock).name
        return data

    def unlock(self):
        """Initiate unlock procedure
        """
        self.transaction(XAPRoutes.XAP_SECURE_UNLOCK)

    def lock(self):
        """Lock device
        """
        self.transaction(XAPRoutes.XAP_SECURE_LOCK)

    def reset(self):
        """Request device reboot to bootloader - Requires previous unlock
        """
        status = self.int_transaction(XAPRoutes.QMK_BOOTLOADER_JUMP)
        return status == 1

    def reinit(self):
        """Request device reset EEPROM - Requires previous unlock
        """
        status = self.int_transaction(XAPRoutes.QMK_EEPROM_RESET)
        return status == 1
