#
#             LUFA Library
#     Copyright (C) Dean Camera, 2009.
#              
#  dean [at] fourwalledcubicle [dot] com
#      www.fourwalledcubicle.com
#

# Makefile to build all the LUFA Device Demos. Call with "make all" to
# rebuild all Device demos.

# Projects are pre-cleaned before each one is built, to ensure any
# custom LUFA library build options are reflected in the compiled
# code.

all:
	make -C AudioInput clean
	make -C AudioInput all

	make -C AudioOutput clean
	make -C AudioOutput all

	make -C CDC clean
	make -C CDC all

	make -C DualCDC clean
	make -C DualCDC all

	make -C GenericHID clean
	make -C GenericHID all

	make -C Joystick clean
	make -C Joystick all

	make -C Keyboard clean
	make -C Keyboard all

	make -C KeyboardMouse clean
	make -C KeyboardMouse all

	make -C MassStorage clean
	make -C MassStorage all

	make -C MassStorageKeyboard clean
	make -C MassStorageKeyboard all

	make -C MIDI clean
	make -C MIDI all

	make -C Mouse clean
	make -C Mouse all

	make -C RNDISEthernet clean
	make -C RNDISEthernet all

%:
	make -C AudioInput $@
	make -C AudioOutput $@
	make -C CDC $@
	make -C DualCDC $@
	make -C GenericHID $@
	make -C Joystick $@
	make -C Keyboard $@
	make -C KeyboardMouse $@
	make -C MassStorage $@
	make -C MassStorageKeyboard $@
	make -C MIDI $@
	make -C Mouse $@
	make -C RNDISEthernet $@
