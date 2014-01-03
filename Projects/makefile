#
#             LUFA Library
#     Copyright (C) Dean Camera, 2014.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile to build all the LUFA Projects. Call with "make all" to
# rebuild all projects.

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

# Need to special-case building without a per-project object directory
ifeq ($(OBJDIR),)
   # If no target specified, force "clean all" and disallow parallel build
   ifeq ($(MAKECMDGOALS),)
      MAKECMDGOALS := clean all
      .NOTPARALLEL:
   endif

   # If one of the targets is to build, force "clean" beforehand and disallow parallel build
   ifneq ($(findstring all, $(MAKECMDGOALS)),)
      MAKECMDGOALS := clean $(MAKECMDGOALS)
      .NOTPARALLEL:
   endif
endif

%: $(PROJECT_DIRECTORIES)
	@echo . > /dev/null

$(PROJECT_DIRECTORIES):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(PROJECT_DIRECTORIES)

