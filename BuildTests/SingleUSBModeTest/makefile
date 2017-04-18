#
#             LUFA Library
#     Copyright (C) Dean Camera, 2017.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile for the single USB mode build test.
# This test attempts to build the USB module
# under fixed device and fixed host modes under
# all supported architectures

# Path to the LUFA library core
LUFA_PATH := ../../LUFA/

# Build test cannot be run with multiple parallel jobs
.NOTPARALLEL:

all: begin compile clean end

begin:
	@echo Executing build test "SingleUSBModeTest".
	@echo

end:
	@echo Build test "SingleUSBModeTest" complete.
	@echo

compile:
	@echo Building SingleUSBModeTest for ARCH=AVR8 in device only mode...
	$(MAKE) -f makefile.test clean elf ARCH=AVR8 MCU=at90usb1287 CC_FLAGS='-D USB_DEVICE_ONLY'

	@echo Building SingleUSBModeTest for ARCH=AVR8 in host only mode...
	$(MAKE) -f makefile.test clean elf ARCH=AVR8 MCU=at90usb1287 CC_FLAGS='-D USB_HOST_ONLY'

	@echo Building SingleUSBModeTest for ARCH=XMEGA in device only mode...
	$(MAKE) -f makefile.test clean elf ARCH=XMEGA MCU=atxmega128a1u CC_FLAGS='-D USB_DEVICE_ONLY'

	@echo Building SingleUSBModeTest for ARCH=UC3 in device only mode...
	$(MAKE) -f makefile.test clean elf ARCH=UC3 MCU=uc3a0256 CC_FLAGS='-D USB_DEVICE_ONLY'

	@echo Building SingleUSBModeTest for ARCH=UC3 in host only mode...
	$(MAKE) -f makefile.test clean elf ARCH=UC3 MCU=uc3a0256 CC_FLAGS='-D USB_HOST_ONLY'

clean:
	$(MAKE) -f makefile.test clean ARCH=AVR8 MCU=at90usb1287
	$(MAKE) -f makefile.test clean ARCH=XMEGA MCU=atxmega128a1u
	$(MAKE) -f makefile.test clean ARCH=UC3 MCU=uc3a0256

%:

.PHONY: begin end compile clean

# Include common DMBS build system modules
DMBS_PATH      ?= $(LUFA_PATH)/Build/DMBS/DMBS
include $(DMBS_PATH)/core.mk
