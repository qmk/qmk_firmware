#
#             LUFA Library
#     Copyright (C) Dean Camera, 2011.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile to build all the LUFA Build Tests. Build Tests are
# used to verify the correctness of the LUFA library, and are
# not intended to be modified or compiled by non-developers.

all:
	$(MAKE) -C ModuleTest all
	$(MAKE) -C SingleUSBModeTest all

%:
	$(MAKE) -C ModuleTest $@
	$(MAKE) -C SingleUSBModeTest $@

