# Set the LFK87 hardware version.
#
# A - Green PCB. at90usb1286 Only 3 exist
# B - We don't talk about RevB
# C-D - Black PCB. at90usb646 First public release
#
LFK_REV = C

ifeq ($(LFK_REV), A)
	MCU = at90usb1286
	OPT_DEFS += -DBOOTLOADER_SIZE=8192
else
	MCU = at90usb646
	OPT_DEFS += -DBOOTLOADER_SIZE=4096
endif
OPT_DEFS += -DLFK_TKL_REV_$(LFK_REV)

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
