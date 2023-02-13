# Build Options
#   change yes to no to disable
#
BACKLIGHT_DRIVER = custom

# TODO: These boards need to be converted to RGB Matrix
VPATH += keyboards/lfkeyboards
SRC = TWIlib.c issi.c lighting.c
