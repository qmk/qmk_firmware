# use custom encoder
ENCODER_ENABLE = no
OPT_DEFS += -DENCODER_ENABLE -DENCODER_MAP_ENABLE
SRC += encoder.c drivers/xl9555.c
QUANTUM_LIB_SRC += i2c_master.c

JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog
SRC += analog.c

RGB_MATRIX_DRIVER = custom
SRC += ws2812.c drivers/is31fl3208.c

LTO_ENABLE = yes
