# Build Options
#   change yes to no to disable
#
TAP_DANCE_ENABLE = no       # Enable TapDance functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes           # Nkey Rollover - If this doesn't work, add this to config.h: #define FORCE_NKRO
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
UNICODE_ENABLE = no         # Unicode
UNICODEMAP_ENABLE = no      # Enable extended unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth
AUDIO_ENABLE = no           # Audio output
#VARIABLE_TRACE = no         # Use this to debug changes to variable values
KEY_LOCK_ENABLE = no        # This enables key lock
SPLIT_KEYBOARD = no         # This enables split keyboard support and includes all necessary files located at quantum/split_common
DYNAMIC_MACRO_ENABLE = yes  # QMK supports temporary macros created on the fly. They are defined by the user from the keyboard and are lost when the keyboard is unplugged or otherwise rebooted.
LTO_ENABLE = yes            # Enables Link Time Optimization (LTO) when compiling the keyboard.
VIA_ENABLE = no             # Turn on VIA
