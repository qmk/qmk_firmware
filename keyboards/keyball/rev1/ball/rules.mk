# To support trackball.
POINTING_DEVICE_ENABLE = yes

# settings extracted from common_features.mk for SPLIT_TRANSPORT.
OPT_DEFS += -DSERIAL_DRIVER_BITBANG
QUANTUM_LIB_SRC += serial.c
