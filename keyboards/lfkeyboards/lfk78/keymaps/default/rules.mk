# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#

BOOTMAGIC_ENABLE = no           # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no            # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes           # Audio control and System control(+450)
CONSOLE_ENABLE = no             # Console for debug(+400)
COMMAND_ENABLE = no             # Commands for debug and configuration
NKRO_ENABLE = yes               # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = yes          # Enable keyboard backlight functionality
MIDI_ENABLE = no                # MIDI controls
AUDIO_ENABLE = yes               # Audio output on port C6
UNICODE_ENABLE = no             # Unicode
BLUETOOTH_ENABLE = no           # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = yes           # Enable WS2812 RGB underlight.  Do not enable this with audio at the same time.
RGBLIGHT_CUSTOM_DRIVER = yes    # RGB code is implemented in lefkeyboards, not qmk base
SLEEP_LED_ENABLE = yes          # Breathing sleep LED during USB suspend
TAP_DANCE_ENABLE = no

ISSI_ENABLE = yes           # If the I2C pullup resistors aren't install this must be disabled
WATCHDOG_ENABLE = no       # Resets keyboard if matrix_scan isn't run every 250ms

ifndef QUANTUM_DIR
    include ../../../../Makefile
endif

ifeq ($(strip $(ISSI_ENABLE)), yes)
    TMK_COMMON_DEFS += -DISSI_ENABLE
endif

ifeq ($(strip $(WATCHDOG_ENABLE)), yes)
    TMK_COMMON_DEFS += -DWATCHDOG_ENABLE
endif

# Override the LFK78 hardware version:
#
# B   - first public release, uses atmega32u4, has audio, ISSI matrix split between RGB and backlight
# C-H - at90usb1286, no audio, ISSI device 0 is backlight, 4 is RGB
# J   - at90usb646, C6 audio, ISSI device 0 is backlight, 4 is RGB
# LFK_REV = J
