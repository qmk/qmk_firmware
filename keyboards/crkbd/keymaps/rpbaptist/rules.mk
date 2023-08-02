#This enables Link Time Optimization.This can save a good chunk of space(several KB for me), but the macro and function... functions cause it to error out.
LTO_ENABLE = yes

#Build Options
#change to "no" to disable the options, or define them in the Makefile in
#the appropriate keymap folder that will get included automatically
#
EXTRAKEY_ENABLE    = yes  # Audio control and System control(+450)
NKRO_ENABLE        = yes  # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
DYNAMIC_MACRO_ENABLE = no

MOUSEKEY_ENABLE    = no   # Mouse keys(+4700)
RGBLIGHT_ENABLE    = no   # Enable WS2812 RGB underlight.
BOOTMAGIC_ENABLE   = no   # Virtual DIP switch configuration(+1000)
CONSOLE_ENABLE     = no   # Console for debug(+400)
COMMAND_ENABLE     = no   # Commands for debug and configuration
BACKLIGHT_ENABLE   = no   # Enable keyboard backlight functionality
MIDI_ENABLE        = no   # MIDI controls
AUDIO_ENABLE       = no   # Audio output on port C6
UNICODE_ENABLE     = no   # Unicode
BLUETOOTH_ENABLE   = no   # Enable Bluetooth with the Adafruit EZ-Key HID
SWAP_HANDS_ENABLE  = no   # Enable one-hand typing
GRAVE_ESC_ENABLE   = no
MAGIC_ENABLE       = no
MUSIC_ENABLE       = no

RGB_MATRIX_ENABLE = yes

#Do not enable SLEEP_LED_ENABLE.it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE   = no    # Breathing sleep LED during USB suspend

BOOTLOADER       = qmk-dfu

OLED_ENABLE = yes
OLED_DRIVER = SSD1306

DEBOUNCE_TYPE = sym_eager_pk

ifeq ($(strip $(THEME)), godspeed)
    OPT_DEFS += -DTHEME_GODSPEED
endif

ifeq ($(strip $(THEME)), godspeed_ares)
    OPT_DEFS += -DTHEME_GODSPEED_ARES
endif

ifeq ($(strip $(THEME)), pulse)
    OPT_DEFS += -DTHEME_PULSE
endif

ifeq ($(strip $(THEME)), laser)
    OPT_DEFS += -DTHEME_LASER
endif

ifeq ($(strip $(THEME)), milkshake)
    OPT_DEFS += -DTHEME_MILKSHAKE
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC += rgb.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC+= oled.c
endif
