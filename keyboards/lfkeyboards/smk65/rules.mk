MCU = at90usb646
OPT_DEFS += -DBOOTLOADER_SIZE=4096

# Extra source files for IS3731 lighting
SRC = TWIlib.c issi.c lighting.c
