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
	@echo Executing build test "ModuleTest".
	@echo

	$(MAKE) -f makefile.avr8 clean
	$(MAKE) -f makefile.avr8

	$(MAKE) -f makefile.xmega clean
	$(MAKE) -f makefile.xmega

	$(MAKE) -f makefile.uc3 clean
	$(MAKE) -f makefile.uc3

	@echo Build test "ModuleTest" complete.
	@echo

clean:
	$(MAKE) -f makefile.avr8 clean
	$(MAKE) -f makefile.xmega clean
	$(MAKE) -f makefile.uc3 clean

%:
	