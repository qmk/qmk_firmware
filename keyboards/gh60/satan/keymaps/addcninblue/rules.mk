# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no      # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes      # Audio control and System control(+450)
CONSOLE_ENABLE = no        # Console for debug(+400)
COMMAND_ENABLE = no        # Commands for debug and configuration
SLEEP_LED_ENABLE = no      # Enables your LED to breathe while your computer is sleeping.
NKRO_ENABLE = yes          # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ # nkro-doesnt-work
BACKLIGHT_ENABLE = yes     # Enable keyboard backlight functionality
MIDI_ENABLE = no           # MIDI controls
AUDIO_ENABLE = no          # Audio output (needs a pin configured in config.h, see docs/feature_audio.md)
UNICODEMAP_ENABLE = no     # This allows sending unicode symbols using X(<unicode>) in your keymap.
UNICODE_ENABLE = no        # Unicode
UCIS_ENABLE = no           # Keep in mind that not all will work (See WinCompose for details on Windows).
BLUETOOTH_ENABLE = no      # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no       # Enable WS2812 RGB underlight. 
SLEEP_LED_ENABLE = no      # Breathing sleep LED during USB suspend
API_SYSEX_ENABLE = no      # This enables using the Quantum SYSEX API to send strings
