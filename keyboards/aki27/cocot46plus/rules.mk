SRC += matrix.c
CUSTOM_MATRIX = lite
POINTING_DEVICE_DRIVER = adns5050
SPACE_CADET_ENABLE = no
# A regular Pro Micro may work if this line is removed
# but some features may need to be disabled for the firmware to fit in the storage.
CONVERT_TO=promicro_rp2040
