#
#             LUFA Library
#     Copyright (C) Dean Camera, 2009.
#              
#  dean [at] fourwalledcubicle [dot] com
#      www.fourwalledcubicle.com
#

# Makefile to build all the LUFA Projects. Call with "make all" to
# rebuild all projects.

# Projects are pre-cleaned before each one is built, to ensure any
# custom LUFA library build options are reflected in the compiled
# code.

all:
	make -C Benito clean
	make -C Benito all

	make -C Magstripe clean
	make -C Magstripe all

	make -C MissileLauncher clean
	make -C MissileLauncher all

%:
	make -C Benito $@
	make -C Magstripe $@
	make -C MissileLauncher $@
