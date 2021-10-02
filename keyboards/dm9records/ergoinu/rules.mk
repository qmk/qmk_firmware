# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = no       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = no       # Enable WS2812 RGB underlight.
SUBPROJECT_rev1 = no
USE_I2C = no               # i2c is not supported
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

CUSTOM_MATRIX = yes
SRC += matrix.c serial.c split_util.c

# ergoinu configs
DISABLE_PROMICRO_LEDs = yes

ifneq ($(strip $(ERGOINU)),)
  ifeq ($(findstring promicroled, $(ERGOINU)), promicroled)
    DISABLE_PROMICRO_LEDs = no
  endif
endif

ifeq ($(strip $(DISABLE_PROMICRO_LEDs)), yes)
  OPT_DEFS += -DDISABLE_PROMICRO_LEDs
endif
