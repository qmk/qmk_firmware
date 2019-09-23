
RGBLIGHT_ENABLE = no

# it should exist either in <this_dir>/ld/
MCU_LDSCRIPT = nrf52840
MCU_SERIES = NRF52840
NRFSDK_ROOT := $(NRFSDK15_ROOT) #Path to nRF SDK v15.0.0

# project specific files
#SRC =	matrix.c

# NRF_SEPARATE = master
#CFLAGS += -DNRF_XTAL_32MHZ