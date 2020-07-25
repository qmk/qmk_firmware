LINK_TIME_OPTIMIZATION_ENABLE = yes  # if firmware size over limit, try this option
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight.

USER_NAME := bottilabo_onehand

# If you want to change the display of OLED, you need to change here
SRC +=  bottilabo_onehand.c \
		keyboard.c
