#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
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
LUFA_PATH         = ../../LUFA/

all: begin compile clean end

begin:
	@echo Executing build test "SingleUSBModeTest".
	@echo

end:
	@echo Build test "SingleUSBModeTest" complete.
	@echo

compile:
	$(MAKE) -s -f makefile.test clean elf ARCH=AVR8 MCU=at90usb1287 CCFLAGS='-D USB_DEVICE_ONLY'
	$(MAKE) -s -f makefile.test clean elf ARCH=AVR8 MCU=at90usb1287 CCFLAGS='-D USB_HOST_ONLY'

	$(MAKE) -s -f makefile.test clean elf ARCH=XMEGA MCU=atxmega128a1u CCFLAGS='-D USB_DEVICE_ONLY'
	
	$(MAKE) -s -f makefile.test clean elf ARCH=UC3 MCU=uc3a0256 CCFLAGS='-D USB_DEVICE_ONLY'
	$(MAKE) -s -f makefile.test clean elf ARCH=UC3 MCU=uc3a0256 CCFLAGS='-D USB_HOST_ONLY'

clean:
	$(MAKE) -s -f makefile.test clean ARCH=AVR8
	$(MAKE) -s -f makefile.test clean ARCH=XMEGA
	$(MAKE) -s -f makefile.test clean ARCH=UC3

%:

.PHONY: begin end compile clean

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa.core.in
