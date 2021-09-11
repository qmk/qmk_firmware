# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes    # Mouse keys
EXTRAKEY_ENABLE = yes    # Audio control and System control
CONSOLE_ENABLE = no      # Console for debug
COMMAND_ENABLE = yes     # Commands for debug and configuration
NKRO_ENABLE = yes        # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = no     # Enable keyboard underlight functionality
BACKLIGHT_ENABLE = no    # Enable keyboard backlight functionality
AUDIO_ENABLE = no
UNICODE_ENABLE = yes     # Unicode
BLUETOOTH_ENABLE = no    # Enable Bluetooth with the Adafruit EZ-Key HID
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend
AUDIO_ENABLE = no        # Audio output on port C6

OLED_ENABLE = yes
OLED_DRIVER = SSD1306 # Enable OLED display support
ENCODER_ENABLE = yes     # Enable encoder support

