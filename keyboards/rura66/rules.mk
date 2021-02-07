# MCU name
MCU = atmega32u4

# Bootloader
BOOTLOADER = caterina

# change yes to no to disable
#
# BOOTMAGIC_ENABLE = no   # Virtual DIP switch configuration
# MOUSEKEY_ENABLE = no    # Mouse keys
# EXTRAKEY_ENABLE = no    # Audio control and System control
# CONSOLE_ENABLE = no     # Console for debug
# COMMAND_ENABLE = no     # Commands for debug and configuration
# NKRO_ENABLE = no        # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
# BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality
# MIDI_ENABLE = no        # MIDI controls
# AUDIO_ENABLE = no       # Audio output on port C6
# UNICODE_ENABLE = no     # Unicode
# BLUETOOTH_ENABLE = no   # Enable Bluetooth with the Adafruit EZ-Key HID
# RGBLIGHT_ENABLE = no    # Enable WS2812 RGB underlight.
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
# SLEEP_LED_ENABLE = no   # Breathing sleep LED during USB suspend

#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = no        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = yes       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
BLUETOOTH_ENABLE = no       # Enable Bluetooth
AUDIO_ENABLE = no           # Audio output

DEFAULT_FOLDER = rura66/rev1
