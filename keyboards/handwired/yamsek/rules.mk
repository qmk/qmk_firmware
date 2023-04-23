
# override quantums matrix.c with custom matrix file
#   which uses a row-oriented internal data-structure, we use a column oriented
#   that was inherited from the I2C/MCP23018 code of the ergodox/ez
CUSTOM_MATRIX = yes
SRC += matrix.c

RGB_MATRIX_ENABLE = no
RGBLIGHT_ENABLE = no
RGBLIGHT_DRIVER = WS2812

VPATH += drivers/gpio
SRC += mcp23018.c
QUANTUM_LIB_SRC += i2c_master.c
OPT_DEFS += -DHAL_USE_I2C=TRUE

DEFAULT_FOLDER = handwired/yamsek/atmega32u4
