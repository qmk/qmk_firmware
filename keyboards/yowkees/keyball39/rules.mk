# Optical sensor driver for trackball.
POINTING_DEVICE_DRIVER = pmw3360

SRC += lib/oledkit/oledkit.c    # OLED utility for Keyball series.

# Include common library
SRC += lib/keyball/keyball.c
