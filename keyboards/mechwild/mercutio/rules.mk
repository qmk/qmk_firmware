# MCU name
MCU = atmega328p

# Bootloader selection
BOOTLOADER = USBasp

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite     # Virtual DIP switch configuration
<<<<<<< HEAD
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
=======
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
>>>>>>> 3dc5e5af388fce6bd2619730c221be3ac71286dd
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
<<<<<<< HEAD
MIDI_ENABLE = no            # MIDI support
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no           # Audio output on port C6
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
HD44780_ENABLE = no         # Enable support for HD44780 based LCDs
ENCODER_ENABLE = yes        # Enable support for EC11 Rotary Encoder
OLED_DRIVER_ENABLE = yes    # Enable Support for SSD1306 or SH1106 OLED Displays; Communicating over I2C
=======
BLUETOOTH_ENABLE = no       # Enable Bluetooth
AUDIO_ENABLE = no           # Audio output
ENCODER_ENABLE = yes
OLED_DRIVER_ENABLE = yes
>>>>>>> 3dc5e5af388fce6bd2619730c221be3ac71286dd
