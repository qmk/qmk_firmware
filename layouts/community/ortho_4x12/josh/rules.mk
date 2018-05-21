ifneq (,$(findstring lets_split,$(KEYBOARD)))
BACKLIGHT_ENABLE = no
BACKLIGHT_BREATHING = no
AUDIO_ENABLE = no
USE_I2C = yes
else
BACKLIGHT_ENABLE = yes
BACKLIGHT_BREATHING = yes
AUDIO_ENABLE = yes
endif
