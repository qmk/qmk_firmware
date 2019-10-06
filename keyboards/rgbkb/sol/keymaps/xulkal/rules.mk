# Overridden build options from rev1 & rev2

# RGB Options
RGBLIGHT_ENABLE         = no        # Enable global lighting effects. Do not enable with RGB Matrix
RGBLIGHT_ANIMATIONS     = no        # LED animations
LED_MIRRORED            = no        # Mirror LEDs across halves 
RGB_MATRIX_ENABLE       = WS2812    # Enable per-key coordinate based RGB effects. Do not enable with RGBlight
FULLHAND_ENABLE         = yes       # Enables the additional 24 Full Hand LEDs

# Misc
OLED_DRIVER_ENABLE      = yes       # Enable the OLED Driver

# Not using the encoder for rev1
ifeq 
    ENCODER_ENABLE = no
	RGB_OLED_MENU = no
else
	ENCODER_ENABLE = yes
	RGB_OLED_MENU = 0
endif

# Do not edit past here

include keyboards/$(KEYBOARD)/post_rules.mk

