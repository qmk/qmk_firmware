# Set the LFK78 hardware version.
#
# B   - first public release, uses atmega32u4, has audio, ISSI matrix split between RGB and backlight
# C-H - at90usb1286, no audio, ISSI device 0 is backlight, 4 is RGB
# J   - at90usb646, C6 audio, ISSI device 0 is backlight, 4 is RGB
LFK_REV = J

ifeq ($(LFK_REV), B)
    MCU = atmega32u4
    OPT_DEFS += -DBOOTLOADER_SIZE=4096
else ifeq ($(LFK_REV), J)
    MCU = at90usb646
    OPT_DEFS += -DBOOTLOADER_SIZE=4096
else
    MCU = at90usb1286
    OPT_DEFS += -DBOOTLOADER_SIZE=8192
endif
OPT_DEFS += -DLFK_REV_$(LFK_REV)
OPT_DEFS += -DLFK_REV_STRING=\"Rev$(LFK_REV)\"

# Extra source files for IS3731 lighting
SRC = TWIlib.c issi.c lighting.c

# Processor frequency.
F_CPU = 16000000

# Target architecture (see library "Board Types" documentation).
ARCH = AVR8

# Input clock frequency.
F_USB = $(F_CPU)

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT
