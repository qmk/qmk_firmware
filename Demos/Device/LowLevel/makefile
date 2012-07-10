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

# This makefile is potentially infinitely recursive if something really bad
# happens when determining the set of project directories - hard-abort if
# more than 10 levels deep to avoid angry emails.
ifeq ($(MAKELEVEL), 10)
   $(error EMERGENCY ABORT: INFINITE RECURSION DETECTED)
endif

# If building without a per-project object directory, we can't build in parallel
ifeq ($(OBJDIR),)
   .NOTPARALLEL:

   # Ensure projects are pre-cleaned if the target is the default or "all"
   ifeq ($(MAKECMDGOALS),)
      MAKECMDGOALS := clean all
   endif
   ifneq ($(findstring all, $(MAKECMDGOALS)),)
      MAKECMDGOALS := clean $(MAKECMDGOALS)
   endif
endif

%: $(PROJECT_DIRECTORIES)
	@echo . > /dev/null

$(PROJECT_DIRECTORIES):
	@$(MAKE) -C $@ $(MAKECMDGOALS)
    
.PHONY: $(PROJECT_DIRECTORIES)
