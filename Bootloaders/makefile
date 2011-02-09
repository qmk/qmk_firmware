#
#             LUFA Library
#     Copyright (C) Dean Camera, 2011.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile to build all the LUFA USB Bootloaders. Call with "make all" to
# rebuild all bootloaders.

# Bootloaders are pre-cleaned before each one is built, to ensure any
# custom LUFA library build options are reflected in the compiled
# code.

all:
	$(MAKE) -C CDC clean
	$(MAKE) -C CDC all

	$(MAKE) -C HID clean
	$(MAKE) -C HID all

	$(MAKE) -C DFU clean
	$(MAKE) -C DFU all

%:
	$(MAKE) -C CDC $@
	$(MAKE) -C DFU $@
	$(MAKE) -C HID $@

