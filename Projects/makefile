#
#             LUFA Library
#     Copyright (C) Dean Camera, 2011.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile to build all the LUFA Projects. Call with "make all" to
# rebuild all projects.

# Projects are pre-cleaned before each one is built, to ensure any
# custom LUFA library build options are reflected in the compiled
# code.

all:
	$(MAKE) -C AVRISP-MKII clean
	$(MAKE) -C AVRISP-MKII all

	$(MAKE) -C Benito clean
	$(MAKE) -C Benito all

	$(MAKE) -C LEDNotifier clean
	$(MAKE) -C LEDNotifier all

	$(MAKE) -C Magstripe clean
	$(MAKE) -C Magstripe all

	$(MAKE) -C MIDIToneGenerator clean
	$(MAKE) -C MIDIToneGenerator all

	$(MAKE) -C MissileLauncher clean
	$(MAKE) -C MissileLauncher all

	$(MAKE) -C RelayBoard clean
	$(MAKE) -C RelayBoard all

	$(MAKE) -C TempDataLogger clean
	$(MAKE) -C TempDataLogger all

	$(MAKE) -C USBtoSerial clean
	$(MAKE) -C USBtoSerial all

	$(MAKE) -C Webserver clean
	$(MAKE) -C Webserver all

	$(MAKE) -C XPLAINBridge clean
	$(MAKE) -C XPLAINBridge all

%:
	$(MAKE) -C AVRISP-MKII $@
	$(MAKE) -C Benito $@
	$(MAKE) -C LEDNotifier $@
	$(MAKE) -C Magstripe $@
	$(MAKE) -C MissileLauncher $@
	$(MAKE) -C RelayBoard $@
	$(MAKE) -C TempDataLogger $@
	$(MAKE) -C USBtoSerial $@
	$(MAKE) -C Webserver $@
	$(MAKE) -C XPLAINBridge $@

