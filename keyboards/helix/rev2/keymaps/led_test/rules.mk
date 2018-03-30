
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE = no       # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
# Helix keyboard : see ./config.h: RGBLED_NUM 6 or 32
# Helix keyboard : RGBLIGHT_ENABLE = no or yes
RGBLIGHT_ENABLE = yes-but-local        # Enable WS2812 RGB underlight.  Do not enable this with audio at the same time.
ONEHAND_ENABLE = no        # Enable one-hand typing

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif

#copy from common_features.mk and modify rgblight.c
    OPT_DEFS += -DRGBLIGHT_ENABLE
    SRC += rgblight.c
    CIE1931_CURVE = yes
    LED_BREATHING_TABLE = yes
    ifeq ($(strip $(RGBLIGHT_CUSTOM_DRIVER)), yes)
        OPT_DEFS += -DRGBLIGHT_CUSTOM_DRIVER
    else
         SRC += ws2812.c
    endif
