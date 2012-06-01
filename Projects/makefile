#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
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
	$(MAKE) -s -C AVRISP-MKII clean all
	$(MAKE) -s -C Benito clean all
	$(MAKE) -s -C HIDReportViewer clean all
	$(MAKE) -s -C LEDNotifier clean all
	$(MAKE) -s -C Magstripe clean all
	$(MAKE) -s -C MediaController clean all
	$(MAKE) -s -C MIDIToneGenerator clean all
	$(MAKE) -s -C MissileLauncher clean all
	$(MAKE) -s -C RelayBoard clean all
	$(MAKE) -s -C SerialToLCD clean all
	$(MAKE) -s -C TempDataLogger clean all
	$(MAKE) -s -C USBtoSerial clean all
	$(MAKE) -s -C Webserver clean all
	$(MAKE) -s -C XPLAINBridge clean all

%:
	$(MAKE) -s -C AVRISP-MKII $@
	$(MAKE) -s -C Benito $@
	$(MAKE) -s -C HIDReportViewer $@	
	$(MAKE) -s -C LEDNotifier $@
	$(MAKE) -s -C Magstripe $@
	$(MAKE) -s -C MediaController $@
	$(MAKE) -s -C MIDIToneGenerator $@	
	$(MAKE) -s -C MissileLauncher $@
	$(MAKE) -s -C RelayBoard $@
	$(MAKE) -s -C SerialToLCD $@
	$(MAKE) -s -C TempDataLogger $@
	$(MAKE) -s -C USBtoSerial $@
	$(MAKE) -s -C Webserver $@
	$(MAKE) -s -C XPLAINBridge $@

