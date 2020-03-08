#
#             LUFA Library
#     Copyright (C) Dean Camera, 2019.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile to build all the LUFA Dual Role Demos. Call with "make all" to
# rebuild all Dual Role demos.

# Projects are pre-cleaned before each one is built, to ensure any
# custom LUFA library build options are reflected in the compiled
# code.

PROJECT_DIRECTORIES := $(shell ls -d */)

# This makefile is potentially infinitely recursive if something really bad
# happens when determining the set of project directories - hard-abort if
# more than 10 levels deep to avoid angry emails.
ifeq ($(MAKELEVEL), 10)
   $(error EMERGENCY ABORT: INFINITE RECURSION DETECTED)
endif

# Build each directory sequentially, even if we are building using multiple
# cores within each project
.NOTPARALLEL:

%: $(PROJECT_DIRECTORIES)
	@echo . > /dev/null

$(PROJECT_DIRECTORIES):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(PROJECT_DIRECTORIES)
