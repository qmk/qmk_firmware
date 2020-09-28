# Build Options
#   change to "no" to disable the options, or define them in the Makefile in 
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
MIDI_ENABLE = no            # MIDI controls
UNICODE_ENABLE = no         # Unicode
UNICODEMAP_ENABLE = yes     # Unicode map
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight. 
API_SYSEX_ENABLE = no

ifeq ($(strip $(KEYBOARD)), planck/rev4)
FAUXCLICKY_ENABLE = yes
BACKLIGHT_ENABLE = yes
AUDIO_ENABLE = no
endif

ifeq ($(strip $(KEYBOARD)), planck/rev6)
DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave
endif

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

