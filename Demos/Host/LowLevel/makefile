#
#             LUFA Library
#     Copyright (C) Dean Camera, 2011.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile to build all the LUFA Host Demos. Call with "make all" to
# rebuild all Host demos.

# Projects are pre-cleaned before each one is built, to ensure any
# custom LUFA library build options are reflected in the compiled
# code.

all:
	$(MAKE) -C GenericHIDHost clean
	$(MAKE) -C GenericHIDHost all

	$(MAKE) -C JoystickHostWithParser clean
	$(MAKE) -C JoystickHostWithParser all

	$(MAKE) -C KeyboardHost clean
	$(MAKE) -C KeyboardHost all

	$(MAKE) -C MassStorageHost clean
	$(MAKE) -C MassStorageHost all

	$(MAKE) -C MIDIHost clean
	$(MAKE) -C MIDIHost all

	$(MAKE) -C MouseHost clean
	$(MAKE) -C MouseHost all

	$(MAKE) -C MouseHostWithParser clean
	$(MAKE) -C MouseHostWithParser all

	$(MAKE) -C PrinterHost clean
	$(MAKE) -C PrinterHost all

	$(MAKE) -C RNDISEthernetHost clean
	$(MAKE) -C RNDISEthernetHost all

	$(MAKE) -C StillImageHost clean
	$(MAKE) -C StillImageHost all

	$(MAKE) -C VirtualSerialHost clean
	$(MAKE) -C VirtualSerialHost all

%:
	$(MAKE) -C GenericHIDHost $@
	$(MAKE) -C JoystickHostWithParser $@
	$(MAKE) -C KeyboardHost $@
	$(MAKE) -C KeyboardHostWithParser $@
	$(MAKE) -C MassStorageHost $@
	$(MAKE) -C MIDIHost $@
	$(MAKE) -C MouseHost $@
	$(MAKE) -C MouseHostWithParser $@
	$(MAKE) -C PrinterHost $@
	$(MAKE) -C RNDISEthernetHost $@
	$(MAKE) -C StillImageHost $@
	$(MAKE) -C VirtualSerialHost $@

