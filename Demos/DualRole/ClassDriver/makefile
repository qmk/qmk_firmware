#
#             LUFA Library
#     Copyright (C) Dean Camera, 2011.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile to build all the LUFA Dual Role Demos. Call with "make all" to
# rebuild all Dual Role demos.

# Projects are pre-cleaned before each one is built, to ensure any
# custom LUFA library build options are reflected in the compiled
# code.

all:
	$(MAKE) -C MouseHostDevice clean
	$(MAKE) -C MouseHostDevice all

%:
	$(MAKE) -C MouseHostDevice $@

