OLED_DRIVER_ENABLE = yes   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # ENables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
RGBLIGHT_STARTUP_ANIMATION = no

BOOTMAGIC_ENABLE = no      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = no      # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no           # USB Nkey Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality on B7 by default
MIDI_ENABLE = no           # MIDI support
UNICODE_ENABLE = no        # Unicode
BLUETOOTH_ENABLE = no      # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no          # Audio output on port C6
FAUXCLICKY_ENABLE = no     # Use buzzer to emulate clicky switches
HD44780_ENABLE = no        # Enable support for HD44780 based LCDs
TAP_DANCE_ENABLE = no

CAPS_WORD_ENABLE = yes

SPLIT_TRANSPORT = mirror

LEADER_ENABLE = yes

SRC += oled_util.c
SRC += rgb_util.c
