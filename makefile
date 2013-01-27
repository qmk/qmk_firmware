#
#             LUFA Library
#     Copyright (C) Dean Camera, 2013.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile to build the LUFA library, projects and demos.

# Call with "make all" to rebuild everything, "make clean" to clean everything,
# "make mostlyclean" to remove all intermediary files but preserve any binaries,
# "make doxygen" to document everything with Doxygen (if installed). Call
# "make help" for additional target build information within a specific project.

all:

%:
	@echo Executing \"make $@\" on all LUFA library elements.
	@echo
	$(MAKE) -C LUFA $@
	$(MAKE) -C Demos $@
	$(MAKE) -C Projects $@
	$(MAKE) -C Bootloaders $@
	@echo
	@echo LUFA \"make $@\" operation complete.
