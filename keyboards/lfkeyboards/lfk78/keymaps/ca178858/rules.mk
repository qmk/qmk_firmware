BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no            # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes           # Audio control and System control(+450)
CONSOLE_ENABLE = no             # Console for debug(+400)
COMMAND_ENABLE = no             # Commands for debug and configuration
NKRO_ENABLE = yes
BACKLIGHT_ENABLE = yes          # Enable keyboard backlight functionality
MIDI_ENABLE = no                # MIDI controls
AUDIO_ENABLE = no              # Audio output on port C6
UNICODE_ENABLE = no             # Unicode
BLUETOOTH_ENABLE = no           # Disable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no           # Enable RGB underlight
SLEEP_LED_ENABLE = yes
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
