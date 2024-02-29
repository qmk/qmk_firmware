UF2_DEVICE_TYPE_ID = 0x9bc1e968
UF2CONV_ARGS = --device-type $(UF2_DEVICE_TYPE_ID)

SRC += lib/common.c lib/mux.c

ANALOG_DRIVER_REQUIRED = yes
