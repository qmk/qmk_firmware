# Path: keyboards/rephlex/2k/rules.mk

SRC += analog.c
SRC += matrix.c
SRC += lut.c
SRC += scanfunctions.c


CUSTOM_MATRIX = lite

WS2812_DRIVER = vendor
RGB_MATRIX_DRIVER = WS2812

OLED_ENABLE = yes
OLED_DRIVER = SSD1306

LTO_ENABLE = yes
OPT = 3

