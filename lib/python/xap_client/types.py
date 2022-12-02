# Copyright 2022 QMK
# SPDX-License-Identifier: GPL-2.0-or-later

################################################################################
#
# 88888888888 888      d8b                .d888 d8b 888               d8b
#     888     888      Y8P               d88P"  Y8P 888               Y8P
#     888     888                        888        888
#     888     88888b.  888 .d8888b       888888 888 888  .d88b.       888 .d8888b
#     888     888 "88b 888 88K           888    888 888 d8P  Y8b      888 88K
#     888     888  888 888 "Y8888b.      888    888 888 88888888      888 "Y8888b.
#     888     888  888 888      X88      888    888 888 Y8b.          888      X88
#     888     888  888 888  88888P'      888    888 888  "Y8888       888  88888P'
#
#                                                       888                 888
#                                                       888                 888
#                                                       888                 888
#    .d88b.   .d88b.  88888b.   .d88b.  888d888 8888b.  888888 .d88b.   .d88888
#   d88P"88b d8P  Y8b 888 "88b d8P  Y8b 888P"      "88b 888   d8P  Y8b d88" 888
#   888  888 88888888 888  888 88888888 888    .d888888 888   88888888 888  888
#   Y88b 888 Y8b.     888  888 Y8b.     888    888  888 Y88b. Y8b.     Y88b 888
#    "Y88888  "Y8888  888  888  "Y8888  888    "Y888888  "Y888 "Y8888   "Y88888
#        888
#   Y8b d88P
#    "Y88P"
#
################################################################################

from collections import namedtuple
from enum import IntFlag, IntEnum
from struct import Struct


class XAPRequest(namedtuple('XAPRequest', 'token length data')):
    fmt = Struct('<HB61s')

    def __new__(cls, *args):
        return super().__new__(cls, *args)

    @classmethod
    def from_bytes(cls, data):
        return cls._make(cls.fmt.unpack(data))

    def to_bytes(self):
        return self.fmt.pack(*list(self))


class XAPResponse(namedtuple('XAPResponse', 'token flags length data')):
    fmt = Struct('<HBB60s')

    def __new__(cls, *args):
        return super().__new__(cls, *args)

    @classmethod
    def from_bytes(cls, data):
        return cls._make(cls.fmt.unpack(data))

    def to_bytes(self):
        return self.fmt.pack(*list(self))


class XAPConfigBacklight(namedtuple('XAPConfigBacklight', 'enable mode val')):
    fmt = Struct('<BBB')

    def __new__(cls, *args):
        return super().__new__(cls, *args)

    @classmethod
    def from_bytes(cls, data):
        return cls._make(cls.fmt.unpack(data))

    def to_bytes(self):
        return self.fmt.pack(*list(self))


class XAPConfigRgblight(namedtuple('XAPConfigRgblight', 'enable mode hue sat val speed')):
    fmt = Struct('<BBBBBB')

    def __new__(cls, *args):
        return super().__new__(cls, *args)

    @classmethod
    def from_bytes(cls, data):
        return cls._make(cls.fmt.unpack(data))

    def to_bytes(self):
        return self.fmt.pack(*list(self))


class XAPConfigRgbMatrix(namedtuple('XAPConfigRgbMatrix', 'enable mode hue sat val speed flags')):
    fmt = Struct('<BBBBBBB')

    def __new__(cls, *args):
        return super().__new__(cls, *args)

    @classmethod
    def from_bytes(cls, data):
        return cls._make(cls.fmt.unpack(data))

    def to_bytes(self):
        return self.fmt.pack(*list(self))


# Spec structs
# TODO: gen outbound object for board_identifiers
# TODO: gen inbound object for get_keymap_keycode
# TODO: gen inbound object for get_encoder_keycode
# TODO: gen inbound object for set_keymap_keycode
# TODO: gen inbound object for set_encoder_keycode
# TODO: gen outbound object for get_config
# TODO: gen inbound object for set_config
# TODO: gen outbound object for get_config
# TODO: gen inbound object for set_config
# TODO: gen outbound object for get_config
# TODO: gen inbound object for set_config
# TODO: gen outbound object for get_config
# TODO: gen inbound object for set_config


class XAPSecureStatus(IntEnum):
    LOCKED = 0x00
    UNLOCKING = 0x01
    UNLOCKED = 0x02


class XAPEventType(IntEnum):
    LOG_MESSAGE = 0x00
    SECURE_STATUS = 0x01
    KB = 0x02
    USER = 0x03


class XAPFlags(IntFlag):
    SUCCESS = 1 << 0
    SECURE_FAILURE = 1 << 1
