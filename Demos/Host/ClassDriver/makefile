#
#             LUFA Library
#     Copyright (C) Dean Camera, 2010.
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
	make -C JoystickHostWithParser clean
	make -C JoystickHostWithParser all	

	make -C KeyboardHost clean
	make -C KeyboardHost all

	make -C KeyboardHostWithParser clean
	make -C KeyboardHostWithParser all

	make -C MIDIHost clean
	make -C MIDIHost all

	make -C MouseHost clean
	make -C MouseHost all

	make -C MouseHostWithParser clean
	make -C MouseHostWithParser all

	make -C MassStorageHost clean
	make -C MassStorageHost all

	make -C PrinterHost clean
	make -C PrinterHost all

	make -C RNDISEthernetHost clean
	make -C RNDISEthernetHost all

	make -C StillImageHost clean
	make -C StillImageHost all

	make -C VirtualSerialHost clean
	make -C VirtualSerialHost all	
	
%:
	make -C JoystickHostWithParser $@
	make -C KeyboardHost $@
	make -C KeyboardHostWithParser $@
	make -C MouseHost $@
	make -C MouseHostWithParser $@
	make -C MassStorageHost $@
	make -C PrinterHost $@
	make -C RNDISEthernetHost $@
	make -C StillImageHost $@
	make -C VirtualSerialHost $@
