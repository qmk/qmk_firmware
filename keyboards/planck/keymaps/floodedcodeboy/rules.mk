ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in 
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no     # Enable Bootmagic Lite


CONSOLE_ENABLE = no       # Console for debug(+400)
COMMAND_ENABLE = yes      # Commands for debug and configuration

MOUSEKEY_ENABLE = no      # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes     # Audio control and System control(+450)

NKRO_ENABLE = yes         # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
UNICODE_ENABLE = no       # Unicode

AUDIO_ENABLE = yes        # Audio output on port C6
MIDI_ENABLE = no          # MIDI controls

BLUETOOTH_ENABLE = no     # Enable Bluetooth with the Adafruit EZ-Key HID

# Lighting
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes      # Enable WS2812 RGB underlight. 

RGB_MATRIX_ENABLE = no

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = yes    # Breathing sleep LED during USB suspend
