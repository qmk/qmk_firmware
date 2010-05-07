#
#             LUFA Library
#     Copyright (C) Dean Camera, 2010.
#              
#  dean [at] fourwalledcubicle [dot] com
#      www.fourwalledcubicle.com
#

# Makefile to build the LUFA library, projects and demos.

# Call with "make all" to rebuild everything, "make clean" to clean everything,
# "make clean_list" to remove all intermediatary files but preserve any binaries,
# "make doxygen" to document everything with Doxygen (if installed) and
# "make clean_doxygen" to remove generated Doxygen documentation from everything.

all:

%:
	@echo Executing \"make $@\" on all LUFA library elements.
	@echo
	$(MAKE) -C LUFA $@ -s
	$(MAKE) -C Demos $@ -s
	$(MAKE) -C Projects $@ -s
	$(MAKE) -C Bootloaders $@ -s
	@echo
	@echo LUFA \"make $@\" operation complete.
