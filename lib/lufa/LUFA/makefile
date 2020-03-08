#
#             LUFA Library
#     Copyright (C) Dean Camera, 2019.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# ---------------------------------------
#  Makefile for the LUFA library itself.
# ---------------------------------------

LUFA_VERSION_NUM := $(shell grep LUFA_VERSION_STRING Version.h | cut -d'"' -f2)

# Default target - no default action when attempting to build the core directly
all:

# Display the LUFA version of this library copy
version:
	@echo "LUFA $(LUFA_VERSION_NUM)"

LUFA_PATH               := .
ARCH                    := {AVR8,UC3,XMEGA}
DOXYGEN_OVERRIDE_PARAMS := QUIET=YES PROJECT_NUMBER=$(LUFA_VERSION_NUM)

# Remove all object and associated files from the LUFA library core
clean:
	rm -f $(LUFA_SRC_ALL_FILES:%.c=%.o)
	rm -f $(LUFA_SRC_ALL_FILES:%.c=%.d)
	rm -f $(LUFA_SRC_ALL_FILES:%.c=%.lst)

# Include LUFA-specific DMBS extension modules
DMBS_LUFA_PATH ?= $(LUFA_PATH)/Build/LUFA
include $(DMBS_LUFA_PATH)/lufa-sources.mk

# Include common DMBS build system modules
DMBS_PATH      ?= $(LUFA_PATH)/Build/DMBS/DMBS
include $(DMBS_PATH)/core.mk
include $(DMBS_PATH)/doxygen.mk

.PHONY: all version
