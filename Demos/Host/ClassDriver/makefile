#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
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
	$(MAKE) -s -C AndroidAccessoryHost clean all
	$(MAKE) -s -C AudioInputHost clean all
	$(MAKE) -s -C AudioOutputHost clean all
	$(MAKE) -s -C JoystickHostWithParser clean all
	$(MAKE) -s -C KeyboardHost clean all
	$(MAKE) -s -C KeyboardHostWithParser clean all
	$(MAKE) -s -C MassStorageHost clean all
	$(MAKE) -s -C MIDIHost clean all
	$(MAKE) -s -C MouseHost clean all
	$(MAKE) -s -C MouseHostWithParser clean all
	$(MAKE) -s -C PrinterHost clean all
	$(MAKE) -s -C RNDISEthernetHost clean all
	$(MAKE) -s -C StillImageHost clean all
	$(MAKE) -s -C VirtualSerialHost clean all

%:
	$(MAKE) -s -C AndroidAccessoryHost $@
	$(MAKE) -s -C AudioInputHost $@
	$(MAKE) -s -C AudioOutputHost $@
	$(MAKE) -s -C JoystickHostWithParser $@
	$(MAKE) -s -C KeyboardHost $@
	$(MAKE) -s -C KeyboardHostWithParser $@
	$(MAKE) -s -C MassStorageHost $@
	$(MAKE) -s -C MIDIHost $@
	$(MAKE) -s -C MouseHost $@
	$(MAKE) -s -C MouseHostWithParser $@
	$(MAKE) -s -C PrinterHost $@
	$(MAKE) -s -C RNDISEthernetHost $@
	$(MAKE) -s -C StillImageHost $@
	$(MAKE) -s -C VirtualSerialHost $@

