#
#             LUFA Library
#     Copyright (C) Dean Camera, 2011.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile for the module build test. This test
# attempts to build as many modules as possible
# under all supported architectures, and include
# all module headers in a simple C and C++
# application.

all:
	@echo Executing build test "SingleUSBModeTest".
	@echo

	$(MAKE) -f makefile.avr8 clean
	$(MAKE) -f makefile.avr8 LUFA_OPTS='-D USB_DEVICE_ONLY'
	$(MAKE) -f makefile.avr8 clean
	$(MAKE) -f makefile.avr8 LUFA_OPTS='-D USB_HOST_ONLY'

	$(MAKE) -f makefile.xmega clean
	$(MAKE) -f makefile.xmega LUFA_OPTS='-D USB_DEVICE_ONLY'

	$(MAKE) -f makefile.uc3 clean
	$(MAKE) -f makefile.uc3 LUFA_OPTS='-D USB_DEVICE_ONLY'
	$(MAKE) -f makefile.uc3 clean
	$(MAKE) -f makefile.uc3 LUFA_OPTS='-D USB_HOST_ONLY'

	@echo Build test "SingleUSBModeTest" complete.
	@echo

clean:
	$(MAKE) -f makefile.avr8 clean
	$(MAKE) -f makefile.xmega clean
	$(MAKE) -f makefile.uc3 clean

%:
	