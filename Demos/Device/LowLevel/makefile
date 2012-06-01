#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile to build all the LUFA Device Demos. Call with "make all" to
# rebuild all Device demos.

# Projects are pre-cleaned before each one is built, to ensure any
# custom LUFA library build options are reflected in the compiled
# code.

all:
	$(MAKE) -s -C AudioInput clean all
	$(MAKE) -s -C AudioOutput clean all
	$(MAKE) -s -C DualVirtualSerial clean all
	$(MAKE) -s -C GenericHID clean all
	$(MAKE) -s -C Joystick clean all
	$(MAKE) -s -C Keyboard clean all
	$(MAKE) -s -C KeyboardMouse clean all
	$(MAKE) -s -C MassStorage clean all
	$(MAKE) -s -C MIDI clean all
	$(MAKE) -s -C Mouse clean all
	$(MAKE) -s -C RNDISEthernet clean all
	$(MAKE) -s -C VirtualSerial clean all

%:
	$(MAKE) -s -C AudioInput $@
	$(MAKE) -s -C AudioOutput $@
	$(MAKE) -s -C DualVirtualSerial $@
	$(MAKE) -s -C GenericHID $@
	$(MAKE) -s -C Joystick $@
	$(MAKE) -s -C Keyboard $@
	$(MAKE) -s -C KeyboardMouse $@
	$(MAKE) -s -C MassStorage $@
	$(MAKE) -s -C MIDI $@
	$(MAKE) -s -C Mouse $@
	$(MAKE) -s -C RNDISEthernet $@
	$(MAKE) -s -C VirtualSerial $@

