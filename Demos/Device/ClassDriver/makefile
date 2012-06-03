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

PROJECT_DIRECTORIES = $(shell ls -d */)

all:
	@$(foreach PROJECT, $(PROJECT_DIRECTORIES), $(MAKE) -s -C $(PROJECT) clean all;)

%:
	@$(foreach PROJECT, $(PROJECT_DIRECTORIES), $(MAKE) -s -C $(PROJECT) $@;)
