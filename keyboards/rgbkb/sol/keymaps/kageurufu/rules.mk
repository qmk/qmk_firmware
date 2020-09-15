# Overridden build options from rev1 & rev2

# Debug Options
CONSOLE_ENABLE          = yes       # Console for debug(+400)
COMMAND_ENABLE          = yes       # Commands for debug and configuration

# RGB Options
RGBLIGHT_ENABLE         = no        # Enable global lighting effects. Do not enable with RGB Matrix
RGBLIGHT_ANIMATIONS     = no        # LED animations
LED_MIRRORED            = no        # Mirror LEDs across halves (enable DIP 1 on slave, and DIP 2 and 3 on master)
RGB_MATRIX_ENABLE       = WS2812    # Enable per-key coordinate based RGB effects. Do not enable with RGBlight

# Userspace implements their own LTO
LTO_ENABLE = no



# Do not edit past here

include keyboards/$(KEYBOARD)/post_rules.mk
