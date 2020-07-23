LINK_TIME_OPTIMIZATION_ENABLE = yes  # if firmware size over limit, try this option
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight.
AUDIO_ENABLE = no           # Audio output on port B6

USER_NAME := bottilabo_onehand

SRC +=  bottilabo_onehand.c \
		keyboard.c
