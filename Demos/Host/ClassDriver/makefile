#
#             LUFA Library
#     Copyright (C) Dean Camera, 2009.
#              
#  dean [at] fourwalledcubicle [dot] com
#      www.fourwalledcubicle.com
#

# Makefile to build all the LUFA Host Demos. Call with "make all" to
# rebuild all Host demos.

# Projects are pre-cleaned before each one is built, to ensure any
# custom LUFA library build options are reflected in the compiled
# code.

all:
	make -C CDCHost clean
	make -C CDCHost all	

	make -C MouseHost clean
	make -C MouseHost all	

%:
	make -C CDCHost $@
	make -C MouseHost $@
