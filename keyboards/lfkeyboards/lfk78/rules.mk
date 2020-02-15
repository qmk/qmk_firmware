# Set the LFK78 hardware version.
#
# B   - first public release, uses atmega32u4, has audio, ISSI matrix split between RGB and backlight
# C-H - at90usb1286, no audio, ISSI device 0 is backlight, 4 is RGB
# J   - at90usb646, C6 audio, ISSI device 0 is backlight, 4 is RGB
LFK_REV = J

ifeq ($(LFK_REV), B)
    MCU = atmega32u4
else ifeq ($(LFK_REV), J)
    MCU = at90usb646
else
    MCU = at90usb1286
endif
BOOTLOADER = atmel-dfu
OPT_DEFS += -DLFK_REV_$(LFK_REV)
OPT_DEFS += -DLFK_REV_STRING=\"Rev$(LFK_REV)\"

# Extra source files for IS3731 lighting
SRC = TWIlib.c issi.c lighting.c

BOOTMAGIC_ENABLE = no           # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no            # Mouse keys
EXTRAKEY_ENABLE = yes           # Audio control and System control
CONSOLE_ENABLE = no             # Console for debug
COMMAND_ENABLE = no             # Commands for debug and configuration
NKRO_ENABLE = yes               # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = yes          # Enable keyboard backlight functionality
BACKLIGHT_DRIVER = custom
MIDI_ENABLE = no                # MIDI controls
AUDIO_ENABLE = yes               # Audio output on port C6
UNICODE_ENABLE = no             # Unicode
BLUETOOTH_ENABLE = no           # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = yes           # Enable WS2812 RGB underlight.
RGBLIGHT_CUSTOM_DRIVER = yes    # RGB code is implemented in lefkeyboards, not qmk base
SLEEP_LED_ENABLE = yes          # Breathing sleep LED during USB suspend
TAP_DANCE_ENABLE = no

ISSI_ENABLE = yes               # If the I2C pullup resistors aren't install this must be disabled
WATCHDOG_ENABLE = no            # Resets keyboard if matrix_scan isn't run every 250ms
CAPSLOCK_LED = no              # Toggle back light LED of Caps Lock


ifeq ($(strip $(ISSI_ENABLE)), yes)
    TMK_COMMON_DEFS += -DISSI_ENABLE
endif

ifeq ($(strip $(WATCHDOG_ENABLE)), yes)
    TMK_COMMON_DEFS += -DWATCHDOG_ENABLE
endif

ifeq ($(strip $(CAPSLOCK_LED)), yes)
    TMK_COMMON_DEFS += -DCAPSLOCK_LED
endif

# # Set the LFK78 hardware version. This is defined in rules.mk, but can be overidden here if desired
# #
# # RevB - first public release, uses atmega32u4, has audio, ISSI matrix split between RGB and backlight
# # RevC/D - at90usb1286, no audio, ISSI device 0 is backlight, 4 is RGB
# #
# # Set to B, C or D
# LFK_REV = D

# ifeq ($(LFK_REV), B)
#   MCU = atmega32u4
# else
#   MCU = at90usb1286
# endif
# OPT_DEFS += -DLFK_REV_$(LFK_REV)
# OPT_DEFS += -DUSB_PRODUCT=\"LFK_Rev$(LFK_REV)\"
