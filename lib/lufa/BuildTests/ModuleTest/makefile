#
#             LUFA Library
#     Copyright (C) Dean Camera, 2017.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile for the module build test. This test
# attempts to build as many modules as possible
# under all supported architectures, and include
# all module headers in a simple C and C++
# application.

# Path to the LUFA library core
LUFA_PATH := ../../LUFA/

# Build test cannot be run with multiple parallel jobs
.NOTPARALLEL:

# List of device families per architecture, one device per architecture sub-family
AVR8_FAMILIES   := at90usb1287 at90usb1286 atmega16u4 atmega16u2 at90usb162
XMEGA_FAMILIES  := atxmega128a1u atxmega128a3u atxmega256a3bu atxmega128a4u atxmega128b1 atxmega128b3 atxmega128c3 atxmega32c4
UC3_FAMILIES    := uc3a0256 uc3a1256 uc3a3256 uc3a4256 uc3b0256 uc3b1256

# List of all device families, with a family postfix
DEVICE_FAMILIES := $(AVR8_FAMILIES:%=%.avr8) $(XMEGA_FAMILIES:%=%.xmega) $(UC3_FAMILIES:%=%.uc3)


all: begin $(DEVICE_FAMILIES) clean end

arch_avr8:  begin $(AVR8_FAMILIES:%=%.avr8) end
arch_xmega: begin $(XMEGA_FAMILIES:%=%.xmega) end
arch_uc3:   begin $(UC3_FAMILIES:%=%.uc3) end

begin:
	@echo Executing build test "ModuleTest".
	@echo

end:
	@echo Build test "ModuleTest" complete.
	@echo

%.avr8:
	@echo Building ModuleTest for ARCH=AVR8 MCU=$(@:%.avr8=%)...
	$(MAKE) -f makefile.test clean elf ARCH=AVR8 MCU=$(@:%.avr8=%)

%.xmega:
	@echo Building ModuleTest for ARCH=XMEGA MCU=$(@:%.xmega=%)...
	$(MAKE) -f makefile.test clean elf ARCH=XMEGA MCU=$(@:%.xmega=%)

%.uc3:
	@echo Building ModuleTest for ARCH=UC3 MCU=$(@:%.uc3=%)...
	$(MAKE) -f makefile.test clean elf ARCH=UC3 MCU=$(@:%.uc3=%)

clean:
	$(MAKE) -f makefile.test clean ARCH=AVR8 MCU=$(firstword $(AVR8_FAMILIES))
	$(MAKE) -f makefile.test clean ARCH=XMEGA MCU=$(firstword $(XMEGA_FAMILIES))
	$(MAKE) -f makefile.test clean ARCH=UC3 MCU=$(firstword $(UC3_FAMILIES))

%:

.PHONY: all arch_avr8 arch_xmega arch_uc3 begin end

# Include common DMBS build system modules
DMBS_PATH      ?= $(LUFA_PATH)/Build/DMBS/DMBS
include $(DMBS_PATH)/core.mk
