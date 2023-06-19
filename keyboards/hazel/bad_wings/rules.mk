TRI_LAYER_ENABLE = yes
CAPS_WORD_ENABLE = yes

SRC += matrix.c

QUANTUM_LIB_SRC += spi_master.c
CUSTOM_MATRIX = lite

POINTING_DEVICE_DRIVER = cirque_pinnacle_spi
POINTING_DEVICE_ENABLE  = yes
