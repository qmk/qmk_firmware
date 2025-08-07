UF2_DEVICE_TYPE_ID = 0x27b9a6ea
UF2CONV_ARGS = --device-type $(UF2_DEVICE_TYPE_ID)

SRC += lib/common.c lib/mux.c

ANALOG_DRIVER_REQUIRED = yes
