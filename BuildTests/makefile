#
#             LUFA Library
#     Copyright (C) Dean Camera, 2017.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile to build all the LUFA Build Tests. Build Tests are
# used to verify the correctness of the LUFA library, and are
# not intended to be modified or compiled by non-developers.

all:

%:
	@echo Executing \"make $@\" on all LUFA build tests.
	@echo
	$(MAKE) -C BoardDriverTest $@
	$(MAKE) -C BootloaderTest $@
	$(MAKE) -C ModuleTest $@
	$(MAKE) -C SingleUSBModeTest $@
	$(MAKE) -C StaticAnalysisTest $@
	@echo
	@echo LUFA build test \"make $@\" operation complete.
