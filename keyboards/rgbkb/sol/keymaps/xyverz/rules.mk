# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys

EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = yes       # Enable global lighting effects. Do not enable with RGB Matrix
LED_MIRRORED = yes          # Mirror LEDs across halves (enable DIP 1 on slave, and DIP 2 and 3 on master)
RGB_MATRIX_ENABLE = no      # Enable per-key coordinate based RGB effects. Do not enable with RGBlight
RGB_MATRIX_KEYPRESSES = no  # Enable reactive per-key effects. Can be very laggy
RGBLIGHT_FULL_POWER = no    # Allow maximum RGB brightness. Otherwise, limited to a safe level for a normal USB-A port
UNICODE_ENABLE = no         # Unicode
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
ENCODER_ENABLE_CUSTOM = no  # Enable rotary encoder
AUDIO_ENABLE = no

OLED_ENABLE = no            # OLED_ENABLE
IOS_DEVICE_ENABLE = no      # Limit max brightness to connect to IOS device (iPad,iPhone)
DEFAULT_FOLDER = rgbkb/sol/rev1
ENCODER_ENABLE = no
OLED_ENABLE = yes
OLED_DRIVER = SSD1306

# Do not edit past here

ifeq ($(strip $(OLED_ENABLE)), yes)
    OPT_DEFS += -DOLED_ENABLE
endif

ifeq ($(strip $(ENCODER_ENABLE_CUSTOM)), yes)
    OPT_DEFS += -DENCODER_ENABLE_CUSTOM
    SRC += common/knob_v2.c

endif

ifeq ($(strip $(IOS_DEVICE_ENABLE)), yes)
    OPT_DEFS += -DIOS_DEVICE_ENABLE

else ifeq ($(strip $(RGBLIGHT_FULL_POWER)), yes)
    OPT_DEFS += -DRGBLIGHT_FULL_POWER
endif

ifeq ($(strip $(RGB_MATRIX_KEYPRESSES)), yes)
    OPT_DEFS += -DRGB_MATRIX_KEYPRESSES
endif

ifeq ($(strip $(LED_MIRRORED)), yes)
    OPT_DEFS += -DLED_MIRRORED
endif
