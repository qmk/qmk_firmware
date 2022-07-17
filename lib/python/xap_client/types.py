from enum import IntFlag, IntEnum


class XAPSecureStatus(IntEnum):
    LOCKED = 0x00
    UNLOCKING = 0x01
    UNLOCKED = 0x02


class XAPFlags(IntFlag):
    FAILURE = 0
    SUCCESS = 1 << 0
    SECURE_FAILURE = 1 << 1


class XAPEventType(IntEnum):
    SECURE = 0x01
    KEYBOARD = 0x02
    USER = 0x03


class XAPRouteError(Exception):
    pass
