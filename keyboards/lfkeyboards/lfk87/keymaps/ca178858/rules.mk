# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#

BOOTMAGIC_ENABLE = no           # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no            # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes           # Audio control and System control(+450)
CONSOLE_ENABLE = yes            # Console for debug(+400)
COMMAND_ENABLE = yes            # Commands for debug and configuration
NKRO_ENABLE = yes               # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = yes          # Enable keyboard backlight functionality
MIDI_ENABLE = no                # MIDI controls
AUDIO_ENABLE = yes              # Audio output on port C6
UNICODE_ENABLE = no             # Unicode
BLUETOOTH_ENABLE = no           # Disable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = yes           # Enable RGB underlight
RGBLIGHT_CUSTOM_DRIVER = yes    # RGB code is implemented in lefkeyboards, not WS2812
SLEEP_LED_ENABLE = yes          # Breathing sleep LED during USB suspend
TAP_DANCE_ENABLE = yes

ISSI_ENABLE = yes			# If the I2C pullup resistors aren't install this must be disabled
WATCHDOG_ENABLE = yes		# Resets keyboard if matrix_scan isn't run every 250ms




# # Set the LFK78 hardware version. This is defined in rules.mk, but can be overidden here if desired
# #
# # RevB - first public release, uses atmega32u4, has audio, ISSI matrix split between RGB and backlight
# # RevC/D - at90usb1286, no audio, ISSI device 0 is backlight, 4 is RGB
# #
# # Set to B, C or D
# LFK_REV = D

# ifeq ($(LFK_REV), B)
# 	MCU = atmega32u4
# else
# 	MCU = at90usb1286
# endif
# OPT_DEFS += -DLFK_REV_$(LFK_REV)
# OPT_DEFS += -DUSB_PRODUCT=\"LFK_Rev$(LFK_REV)\"
