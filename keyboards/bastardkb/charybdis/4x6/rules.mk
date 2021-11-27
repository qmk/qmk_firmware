# The Charybdis' original design uses the Elite-C.
MCU = atmega32u4       # MCU name.
BOOTLOADER = atmel-dfu # Bootloader selection.

# Hardware features.
AUDIO_SUPPORTED = no       # Audio is not supported.
RGB_MATRIX_SUPPORTED = yes # RGB matrix is supported and enabled by default.
RGBLIGHT_SUPPORTED = yes   # RGB underglow is supported, but not enabled by default.

# Software features.
BOOTMAGIC_ENABLE = yes  # Disable Bootmagic Lite.
MOUSEKEY_ENABLE = no    # Disable mouse keys by default, which saves some space by emulating them instead.
EXTRAKEY_ENABLE = yes   # Enable Audio control and System control.
CONSOLE_ENABLE = no     # Disable console, usually used for debug purposes.
COMMAND_ENABLE = no     # Disable commands for debug and configuration.
NKRO_ENABLE = no        # Disable USB Nkey Rollover.  Default to 6KRO.
AUDIO_ENABLE = no       # Audio is not supported.
RGB_MATRIX_ENABLE = yes # RGB matrix is supported and enabled by default.
RGB_MATRIX_DRIVER = WS2812
RGBLIGHT_ENABLE = no    # RGB underglow is supported, but not enabled by default.
BACKLIGHT_ENABLE = no   # Backlight is not supported.
SLEEP_LED_ENABLE = no   # Breathing sleep LED during USB suspend is not supported.

# Charybdis is a split 4x6 keyboard with a maximum of 5 thumb keys (3 on the
# trackball side).
SPLIT_KEYBOARD = yes

# Charybdis uses a trackball.
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3360
# https://qmk.fm/changes/2018-11-16-use-a-single-endpoint-for-hid-reports
MOUSE_SHARED_EP = no # Unify multiple HID interfaces into a single Endpoint.
