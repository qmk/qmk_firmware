# use custom encoder
ENCODER_ENABLE = no
OPT_DEFS += -DENCODER_ENABLE -DENCODER_MAP_ENABLE
SRC += encoder.c drivers/xl9555.c
QUANTUM_LIB_SRC += i2c_master.c

JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog
SRC += analog.c

LTO_ENABLE = yes
