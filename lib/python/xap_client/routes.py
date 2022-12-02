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

class XAPRouteError(Exception):
    pass


class XAPRoutes():
    # XAP
    XAP_VERSION_QUERY = b'\x00\x00'
    XAP_CAPABILITIES_QUERY = b'\x00\x01'
    XAP_SUBSYSTEM_QUERY = b'\x00\x02'
    XAP_SECURE_STATUS = b'\x00\x03'
    XAP_SECURE_UNLOCK = b'\x00\x04'
    XAP_SECURE_LOCK = b'\x00\x05'
    # QMK
    QMK_VERSION_QUERY = b'\x01\x00'
    QMK_CAPABILITIES_QUERY = b'\x01\x01'
    QMK_BOARD_IDENTIFIERS = b'\x01\x02'
    QMK_BOARD_MANUFACTURER = b'\x01\x03'
    QMK_PRODUCT_NAME = b'\x01\x04'
    QMK_CONFIG_BLOB_LEN = b'\x01\x05'
    QMK_CONFIG_BLOB_CHUNK = b'\x01\x06'
    QMK_BOOTLOADER_JUMP = b'\x01\x07'
    QMK_HARDWARE_ID = b'\x01\x08'
    QMK_EEPROM_RESET = b'\x01\x09'
    # KEYMAP
    KEYMAP_CAPABILITIES_QUERY = b'\x04\x01'
    KEYMAP_GET_LAYER_COUNT = b'\x04\x02'
    KEYMAP_GET_KEYMAP_KEYCODE = b'\x04\x03'
    KEYMAP_GET_ENCODER_KEYCODE = b'\x04\x04'
    # REMAPPING
    REMAPPING_CAPABILITIES_QUERY = b'\x05\x01'
    REMAPPING_GET_DYNAMIC_LAYER_COUNT = b'\x05\x02'
    REMAPPING_SET_KEYMAP_KEYCODE = b'\x05\x03'
    REMAPPING_SET_ENCODER_KEYCODE = b'\x05\x04'
    # LIGHTING
    LIGHTING_CAPABILITIES_QUERY = b'\x06\x01'
    LIGHTING_BACKLIGHT = b'\x06\x02'
    LIGHTING_BACKLIGHT_CAPABILITIES_QUERY = b'\x06\x02\x01'
    LIGHTING_BACKLIGHT_GET_ENABLED_EFFECTS = b'\x06\x02\x02'
    LIGHTING_BACKLIGHT_GET_CONFIG = b'\x06\x02\x03'
    LIGHTING_BACKLIGHT_SET_CONFIG = b'\x06\x02\x04'
    LIGHTING_BACKLIGHT_SAVE_CONFIG = b'\x06\x02\x05'
    LIGHTING_RGBLIGHT = b'\x06\x03'
    LIGHTING_RGBLIGHT_CAPABILITIES_QUERY = b'\x06\x03\x01'
    LIGHTING_RGBLIGHT_GET_ENABLED_EFFECTS = b'\x06\x03\x02'
    LIGHTING_RGBLIGHT_GET_CONFIG = b'\x06\x03\x03'
    LIGHTING_RGBLIGHT_SET_CONFIG = b'\x06\x03\x04'
    LIGHTING_RGBLIGHT_SAVE_CONFIG = b'\x06\x03\x05'
    LIGHTING_RGB_MATRIX = b'\x06\x04'
    LIGHTING_RGB_MATRIX_CAPABILITIES_QUERY = b'\x06\x04\x01'
    LIGHTING_RGB_MATRIX_GET_ENABLED_EFFECTS = b'\x06\x04\x02'
    LIGHTING_RGB_MATRIX_GET_CONFIG = b'\x06\x04\x03'
    LIGHTING_RGB_MATRIX_SET_CONFIG = b'\x06\x04\x04'
    LIGHTING_RGB_MATRIX_SAVE_CONFIG = b'\x06\x04\x05'
    # AUDIO
    AUDIO_CAPABILITIES_QUERY = b'\x07\x01'
    AUDIO_GET_CONFIG = b'\x07\x03'
    AUDIO_SET_CONFIG = b'\x07\x04'
    AUDIO_SAVE_CONFIG = b'\x07\x05'
