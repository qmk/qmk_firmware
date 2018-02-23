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
	OPT_DEFS += -DBOOTLOADER_SIZE=8192
else
	MCU = at90usb646
	OPT_DEFS += -DBOOTLOADER_SIZE=4096
endif
OPT_DEFS += -DLFK_TKL_REV_$(LFK_REV)

# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the
#     processor frequency in Hz. You can then use this symbol in your source code to
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#
#     This will be an integer division of F_USB below, as it is sourced by
#     F_USB after it has run through any CPU prescalers. Note that this value
#     does not *change* the processor frequency - it should merely be updated to
#     reflect the processor speed set externally so that the code can use accurate
#     software delays.
F_CPU = 16000000


#
# LUFA specific
#
# Target architecture (see library "Board Types" documentation).
ARCH = AVR8

# Input clock frequency.
#     This will define a symbol, F_USB, in all source code files equal to the
#     input clock frequency (before any prescaling is performed) in Hz. This value may
#     differ from F_CPU if prescaling is used on the latter, and is required as the
#     raw input clock is fed directly to the PLL sections of the AVR for high speed
#     clock generation for the USB and other AVR subsections. Do NOT tack on a 'UL'
#     at the end, this will be done automatically to create a 32-bit value in your
#     source code.
#
#     If no clock division is performed on the input clock inside the AVR (via the
#     CPU clock adjust registers or the clock division fuses), this will be equal to F_CPU.
F_USB = $(F_CPU)

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# ifndef QUANTUM_DIR
# 	include ../../Makefile
# endif


ifeq ($(strip $(ISSI_ENABLE)), yes)
    # TMK_COMMON_DEFS += -DISSI_ENABLE
endif
