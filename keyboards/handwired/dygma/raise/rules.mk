CUSTOM_MATRIX = lite

# TODO(ibash) we don't actually need to enable raw, but there's some side effect
# in the usb driver this triggers that allows mousekeys to work. The same side
# effect happens if console or midi is enabled -- so something to do with
# alternate usb endpoints.

I2C_DRIVER_REQUIRED = yes
SRC += matrix.c

DEFAULT_FOLDER = handwired/dygma/raise/ansi
