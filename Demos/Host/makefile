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

	make -C KeyboardHost clean
	make -C KeyboardHostWithParser all	

	make -C MassStorageHost clean
	make -C MassStorageHost all	

	make -C MouseHost clean
	make -C MouseHost all	

	make -C MouseHostWithParser clean
	make -C MouseHostWithParser all	

	make -C StillImageHost clean
	make -C StillImageHost all	

%:
	make -C CDCHost $@
	make -C KeyboardHost $@
	make -C KeyboardHostWithParser $@
	make -C MassStorageHost $@
	make -C MouseHost $@
	make -C MouseHostWithParser $@
	make -C StillImageHost $@
