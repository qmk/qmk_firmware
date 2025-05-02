# @see `info.json` for config

CUSTOM_MATRIX = yes

OLED_ENABLE = yes
OLED_DRIVER = ssd1306
OLED_TRANSPORT = i2c

SRC += matrix.c \
       candypad_oled.c

OPT_DEFS += -DHAL_USE_I2C=TRUE
