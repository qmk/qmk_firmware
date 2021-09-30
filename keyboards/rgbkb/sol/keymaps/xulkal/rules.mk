# Overridden build options from rev1 & rev2

# RGB Options
RGBLIGHT_ENABLE         = no        # Enable global lighting effects. Do not enable with RGB Matrix
RGBLIGHT_ANIMATIONS     = no        # LED animations
LED_MIRRORED            = no        # Mirror LEDs across halves (enable DIP 1 on slave, and DIP 2 and 3 on master)
RGB_MATRIX_ENABLE       = yes       # Enable per-key coordinate based RGB effects. Do not enable with RGBlight
FULLHAND_ENABLE         = no        # Enables the additional 24 Full Hand LEDs
SF_ENABLE               = no        # Enables the additional 38 Starfighter LEDs

# Misc
OLED_ENABLE     = yes       # Enable the OLED Driver

# Not using the encoder for rev1
ifeq ($(strip $(KEYBOARD)), rgbkb/sol/rev1)
    ENCODER_ENABLE = no
	RGB_OLED_MENU = no
else
	ENCODER_ENABLE = yes
	RGB_OLED_MENU = 0
endif

# Do not edit past here

include keyboards/$(KEYBOARD)/post_rules.mk

