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
# "make doxygen" to document everything with DoxyGen (if installed) and
# "make clean_doxygen" to remove generated Doxygen documentation from everything.

all:

%:
	@echo Executing \"make $@\" on all LUFA library elements.
	@echo
	make -C LUFA/ $@ -s
	make -C Demos/ $@ -s
	make -C Projects/ $@ -s
	make -C Bootloaders/ $@ -s
	@echo
	@echo LUFA \"make $@\" operation complete.
