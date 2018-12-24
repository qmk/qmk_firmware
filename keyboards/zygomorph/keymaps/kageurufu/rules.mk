# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#

BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
COMMAND_ENABLE = yes        # Commands for debug and configuration
CONSOLE_ENABLE = yes        # Console for debug(+400)
# ENCODER_ENABLE = yes        # Enable rotary encoder (+90)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
IOS_DEVICE_ENABLE = no      # Limit max brightness to connect to IOS device (iPad,iPhone)
LED_MIRRORED = yes          # Mirror LEDs across halves (enable DIP 1 on slave, and DIP 2 and 3 on master)
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
OLED_ENABLE = no            # OLED_ENABLE (+5000)
RGB_MATRIX_ENABLE = no      # Enable per-key coordinate based RGB effects. Do not enable with RGBlight (+8500)
RGB_MATRIX_KEYPRESSES = no  # Enable reactive per-key effects. Can be very laggy (+1500)
RGBLIGHT_ANIMATIONS = yes   # LED animations
RGBLIGHT_ENABLE = yes       # Enable global lighting effects. Do not enable with RGB Matrix
RGBLIGHT_FULL_POWER = no    # Allow maximum RGB brightness. Otherwise, limited to a safe level for a normal USB-A port
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
UNICODE_ENABLE = no         # Unicode

# Do not edit past here

ifeq ($(strip $(OLED_ENABLE)), yes)
    OPT_DEFS += -DOLED_ENABLE
endif

ifeq ($(strip $(RGBLIGHT_FULL_POWER)), yes)
    OPT_DEFS += -DRGBLIGHT_FULL_POWER
endif

ifeq ($(strip $(RGB_MATRIX_KEYPRESSES)), yes)
    OPT_DEFS += -DRGB_MATRIX_KEYPRESSES
endif

ifeq ($(strip $(LED_MIRRORED)), yes)
    OPT_DEFS += -DLED_MIRRORED
endif

# Link time optimization, should save on firmware size
EXTRAFLAGS += -flto
