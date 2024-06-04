# Optical sensor driver for trackball.
POINTING_DEVICE_DRIVER = custom
SRC += drivers/pmw3360/pmw3360.c
QUANTUM_LIB_SRC += spi_master.c # Optical sensor use SPI to communicate

SRC += lib/oledkit/oledkit.c    # OLED utility for Keyball series.

# Include common library
SRC += lib/keyball/keyball.c
