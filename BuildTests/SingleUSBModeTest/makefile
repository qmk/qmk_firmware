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

all: begin compile clean end

begin:
	@echo Executing build test "SingleUSBModeTest".
	@echo

end:
	@echo Build test "SingleUSBModeTest" complete.
	@echo

compile:
	$(MAKE) -s -f makefile.avr8 clean
	$(MAKE) -s -f makefile.avr8 LUFA_OPTS='-D USB_DEVICE_ONLY' elf
	$(MAKE) -s -f makefile.avr8 clean
	$(MAKE) -s -f makefile.avr8 LUFA_OPTS='-D USB_HOST_ONLY' elf

	$(MAKE) -s -f makefile.xmega clean
	$(MAKE) -s -f makefile.xmega LUFA_OPTS='-D USB_DEVICE_ONLY' elf
	
	$(MAKE) -s -f makefile.uc3 clean
	$(MAKE) -s -f makefile.uc3 LUFA_OPTS='-D USB_DEVICE_ONLY' elf
	$(MAKE) -s -f makefile.uc3 clean
	$(MAKE) -s -f makefile.uc3 LUFA_OPTS='-D USB_HOST_ONLY' elf

clean:
	$(MAKE) -s -f makefile.avr8 clean
	$(MAKE) -s -f makefile.xmega clean
	$(MAKE) -s -f makefile.uc3 clean

%:
	