# MCU name
MCU = atmega32u4

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
AUDIO_ENABLE        = yes  # Audio output on port C6
BACKLIGHT_ENABLE    = no   # Enable keyboard backlight functionality
BLUETOOTH_ENABLE    = no   # Enable Bluetooth with the Adafruit EZ-Key HID
BOOTMAGIC_ENABLE    = no   # Virtual DIP switch configuration
COMMAND_ENABLE      = no   # Commands for debug and configuration
CONSOLE_ENABLE      = no   # Console for debug
DEBUG_ENABLE        = no   # Enable more debug info
EXTRAKEY_ENABLE     = yes  # Audio control and System control
MIDI_ENABLE         = no   # MIDI controls
MOUSEKEY_ENABLE     = no   # Mouse keys
NKRO_ENABLE         = no   # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE     = yes  # Enable WS2812 RGB underlight.
UNICODE_ENABLE      = no   # Unicode
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE    = no   # Breathing sleep LED during USB suspend

LAYOUTS = ortho_4x12

DEFAULT_FOLDER = vitamins_included/rev2

LINK_TIME_OPTIMIZATION_ENABLE = yes
