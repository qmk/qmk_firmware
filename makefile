#
#             LUFA Library
#     Copyright (C) Dean Camera, 2009.
#              
#  dean [at] fourwalledcubicle [dot] com
#      www.fourwalledcubicle.com
#

# Makefile to build the LUFA library, projects and demos.

# Call with "make all" to rebuild everything, "make clean" to clean everything,
# "make clean_list" to remove all intermediatary files but preserve any binaries,
# "make doxygen" to document everything with DoxyGen (if installed) and
# "make clean_doxygen" to remove generated Doxygen documentation from everything.

# It is suggested that for the master build, the --quiet switch is passed to make,
# to remove all the commands from the output. This gives a much easier to read
# report of the entire build process.

all:

%:
	@echo Executing \"make $@\" on all LUFA library elements.
	@echo
	make -C LUFA/ $@
	make -C Demos/ $@
	make -C Projects/ $@
	make -C Bootloaders/ $@
	@echo
	@echo LUFA \"make $@\" operation complete.
