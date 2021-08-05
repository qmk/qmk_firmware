# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover - If this doesn't work, add this to config.h: #define FORCE_NKRO
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
MIDI_ENABLE = no            # MIDI support
UNICODE_ENABLE = no         # Unicode
UNICODEMAP_ENABLE = no      # Enable extended unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no           # Audio output on port C6
#VARIABLE_TRACE = no         # Use this to debug changes to variable values
API_SYSEX_ENABLE = no       # This enables using the Quantum SYSEX API to send strings
KEY_LOCK_ENABLE = no        # This enables key lock
SPLIT_KEYBOARD = no         # This enables split keyboard support and includes all necessary files located at quantum/split_common
TAP_DANCE_ENABLE = no       # Enable TapDance functionality
