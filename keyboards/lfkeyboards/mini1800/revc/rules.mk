# MCU name
MCU = at90usb646

# Bootloader selection
BOOTLOADER = atmel-dfu
OPT_DEFS += -DLFK_TKL_REV_$(LFK_REV)

# Extra source files for IS3731 lighting
SRC = TWIlib.c issi.c lighting.c

# Build Options
#   change yes to no to disable
#
BACKLIGHT_DRIVER = custom
