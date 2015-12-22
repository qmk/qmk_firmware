#
#             LUFA Library
#     Copyright (C) Dean Camera, 2015.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

DMBS_BUILD_MODULES         +=
DMBS_BUILD_TARGETS         +=
DMBS_BUILD_MANDATORY_VARS  += LUFA_PATH ARCH F_USB
DMBS_BUILD_OPTIONAL_VARS   += BOARD
DMBS_BUILD_PROVIDED_VARS   +=
DMBS_BUILD_PROVIDED_MACROS +=

# -----------------------------------------------------------------------------
#               LUFA Core Build Buildsystem Makefile Module.
# -----------------------------------------------------------------------------
# DESCRIPTION:
#   Subclass of the standard DMBS GCC build module, with LUFA specific
#   extensions. This module provides the core build rules for the compilation
#   of LUFA projects using GCC.
# -----------------------------------------------------------------------------
# TARGETS:
#
#    (None)
#
# MANDATORY PARAMETERS:
#
#    LUFA_PATH                 - Path to the LUFA library core
#    ARCH                      - Device architecture name
#    F_USB                     - Speed of the USB core clock, in Hz
#
# OPTIONAL PARAMETERS:
#
#    BOARD                     - LUFA board drivers to use
#
# PROVIDED VARIABLES:
#
#    (None)
#
# PROVIDED MACROS:
#
#    (None)
#
# -----------------------------------------------------------------------------

SHELL = /bin/sh

ERROR_IF_UNSET   ?= $(if $(filter undefined, $(origin $(strip $(1)))), $(error Makefile $(strip $(1)) value not set))
ERROR_IF_EMPTY   ?= $(if $(strip $($(strip $(1)))), , $(error Makefile $(strip $(1)) option cannot be blank))
ERROR_IF_NONBOOL ?= $(if $(filter Y N, $($(strip $(1)))), , $(error Makefile $(strip $(1)) option must be Y or N))

# Sanity check user supplied values
$(call ERROR_IF_EMPTY, LUFA_PATH)
$(call ERROR_IF_EMPTY, ARCH)
$(call ERROR_IF_EMPTY, F_USB)

# Default values of optionally user-supplied variables
BOARD ?= NONE

# Determine the utility prefix to use for the selected architecture
ifeq ($(ARCH), XMEGA)
   $(warning The XMEGA device support is currently EXPERIMENTAL (incomplete and/or non-functional), and is included for preview purposes only.)
else ifeq ($(ARCH), UC3)
   $(warning The UC3 device support is currently EXPERIMENTAL (incomplete and/or non-functional), and is included for preview purposes only.)
endif

# LUFA specific standard build options
C_FLAGS += -I. -I$(patsubst %/,%,$(LUFA_PATH))/..
C_FLAGS += -DARCH=ARCH_$(ARCH) -DBOARD=BOARD_$(BOARD) -DF_USB=$(F_USB)UL

# This flag is required for bootloaders as GCC will emit invalid jump table
# assembly code for devices with large amounts of flash; the jump table target
# is extracted from FLASH without using the correct ELPM instruction, resulting
# in a pseudo-random jump target.
C_FLAGS += -fno-jump-tables

DMBS_PATH := $(LUFA_PATH)/Build/DMBS/DMBS
include $(DMBS_PATH)/gcc.mk
