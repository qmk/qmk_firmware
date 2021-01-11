# Set the LFK87 hardware version.
#
# RevA - Green PCB. at90usb1286 Only 3 exist
# RevB - We don't talk about RevB
# RevC - Black PCB. at90usb646 First public release
#
# Set to A or C
LFK_REV = C

ifeq ($(LFK_REV), A)
    MCU = at90usb1286
else
    MCU = at90usb646
endif
BOOTLOADER = atmel-dfu
OPT_DEFS += -DLFK_TKL_REV_$(LFK_REV)

# Extra source files for IS3731 lighting
SRC = TWIlib.c issi.c lighting.c

ifeq ($(strip $(ISSI_ENABLE)), yes)
    # TMK_COMMON_DEFS += -DISSI_ENABLE
endif
