#
#             LUFA Library
#     Copyright (C) Dean Camera, 2009.
#              
#  dean [at] fourwalledcubicle [dot] com
#      www.fourwalledcubicle.com
#

# Makefile to build all the LUFA Demos. Call with "make all" to
# rebuild all demos.

# Projects are pre-cleaned before each one is built, to ensure any
# custom LUFA library build options are reflected in the compiled
# code.

all:
	make -C AudioInput clean
	make -C AudioInput all

	make -C AudioOutput clean
	make -C AudioOutput all

	make -C BluetoothHost clean
	make -C BluetoothHost all

	make -C CDC clean
	make -C CDC all

	make -C CDCHost clean
	make -C CDCHost all

	make -C DualCDC clean
	make -C DualCDC all

	make -C Joystick clean
	make -C Joystick all

	make -C KeyboardMouse clean
	make -C KeyboardMouse all

	make -C Keyboard clean
	make -C Keyboard all

	make -C KeyboardFullInt clean
	make -C KeyboardFullInt all

	make -C KeyboardViaInt clean
	make -C KeyboardViaInt all

	make -C KeyboardHost clean
	make -C KeyboardHost all
	
	make -C KeyboardHostWithParser clean
	make -C KeyboardHostWithParser all

	make -C KeyboardHostViaInt clean
	make -C KeyboardHostViaInt all

	make -C MassStorage clean
	make -C MassStorage all

	make -C MassStorageHost clean
	make -C MassStorageHost all

	make -C MIDI clean
	make -C MIDI all

	make -C Mouse clean
	make -C Mouse all

	make -C MouseFullInt clean
	make -C MouseFullInt all

	make -C MouseViaInt clean
	make -C MouseViaInt all
	
	make -C MouseHost clean
	make -C MouseHost all

	make -C MouseHostWithParser clean
	make -C MouseHostWithParser all

	make -C MouseHostViaInt clean
	make -C MouseHostViaInt all

	make -C RNDISEthernet clean
	make -C RNDISEthernet all

	make -C StillImageHost clean
	make -C StillImageHost all

	make -C TestApp clean
	make -C TestApp all

	make -C USBtoSerial clean
	make -C USBtoSerial all

%:
	make -C AudioInput $@
	make -C AudioOutput $@
	make -C BluetoothHost $@
	make -C CDC $@
	make -C CDCHost $@
	make -C DualCDC $@
	make -C Joystick $@
	make -C KeyboardMouse $@
	make -C Keyboard $@
	make -C KeyboardFullInt $@
	make -C KeyboardViaInt $@
	make -C KeyboardHost $@
	make -C KeyboardHostWithParser $@
	make -C KeyboardHostViaInt $@
	make -C MassStorage $@
	make -C MassStorageHost $@
	make -C MIDI $@
	make -C Mouse $@
	make -C MouseFullInt $@
	make -C MouseViaInt $@
	make -C MouseHost $@
	make -C MouseHostWithParser $@
	make -C MouseHostViaInt $@
	make -C RNDISEthernet $@
	make -C StillImageHost $@
	make -C TestApp $@
	make -C USBtoSerial $@