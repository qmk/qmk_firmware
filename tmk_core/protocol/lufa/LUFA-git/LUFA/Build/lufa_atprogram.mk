#
#             LUFA Library
#     Copyright (C) Dean Camera, 2014.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

LUFA_BUILD_MODULES         += ATPROGRAM
LUFA_BUILD_TARGETS         += atprogram atprogram-ee
LUFA_BUILD_MANDATORY_VARS  += MCU TARGET
LUFA_BUILD_OPTIONAL_VARS   += ATPROGRAM_PROGRAMMER ATPROGRAM_INTERFACE ATPROGRAM_PORT
LUFA_BUILD_PROVIDED_VARS   +=
LUFA_BUILD_PROVIDED_MACROS +=

# -----------------------------------------------------------------------------
#             LUFA ATPROGRAM Programmer Buildsystem Makefile Module.
# -----------------------------------------------------------------------------
# DESCRIPTION:
#   Provides a set of targets to re-program a device using the Atmel atprogram
#   utility in AVR Studio 5.x and Atmel Studio 6.0 onwards.
# -----------------------------------------------------------------------------
# TARGETS:
#
#    atprogram                 - Program target FLASH with application using
#                                atprogram
#    atprogram-ee              - Program target EEPROM with application data
#                                using atprogram
#
# MANDATORY PARAMETERS:
#
#    MCU                       - Microcontroller device model name
#    TARGET                    - Application name
#
# OPTIONAL PARAMETERS:
#
#    ATPROGRAM_PROGRAMMER      - Name of programming hardware to use
#    ATPROGRAM_INTERFACE       - Name of programming interface to use
#    ATPROGRAM_PORT            - Name of communication port to use
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

# Default values of optionally user-supplied variables
ATPROGRAM_PROGRAMMER ?= jtagice3
ATPROGRAM_INTERFACE  ?= jtag
ATPROGRAM_PORT       ?=

# Sanity check user supplied values
$(foreach MANDATORY_VAR, $(LUFA_BUILD_MANDATORY_VARS), $(call ERROR_IF_UNSET, $(MANDATORY_VAR)))
$(call ERROR_IF_EMPTY, MCU)
$(call ERROR_IF_EMPTY, TARGET)
$(call ERROR_IF_EMPTY, ATPROGRAM_PROGRAMMER)
$(call ERROR_IF_EMPTY, ATPROGRAM_INTERFACE)

# Output Messages
MSG_ATPROGRAM_CMD    := ' [ATPRGRM] :'

# Construct base atprogram command flags
BASE_ATPROGRAM_FLAGS := --tool $(ATPROGRAM_PROGRAMMER) --interface $(ATPROGRAM_INTERFACE) --device $(MCU)
ifneq ($(ATPROGRAM_PORT),)
   BASE_ATPROGRAM_FLAGS += --port $(ATPROGRAM_PORT)
endif

# Construct the flags to use for the various memory spaces
ifeq ($(ARCH), AVR8)
   ATPROGRAM_FLASH_FLAGS  := --chiperase --flash
   ATPROGRAM_EEPROM_FLAGS := --eeprom
else ifeq ($(ARCH), XMEGA)
   ATPROGRAM_FLASH_FLAGS  := --erase --flash
   ATPROGRAM_EEPROM_FLAGS := --eeprom
else ifeq ($(ARCH), UC3)
   ATPROGRAM_FLASH_FLAGS  := --erase
   ATPROGRAM_EEPROM_FLAGS := --eeprom
else
   $(error Unsupported architecture "$(ARCH)")
endif

# Programs in the target FLASH memory using ATPROGRAM
atprogram: $(TARGET).elf $(MAKEFILE_LIST)
	@echo $(MSG_ATPROGRAM_CMD) Programming device \"$(MCU)\" FLASH using \"$(ATPROGRAM_PROGRAMMER)\"
	atprogram $(BASE_ATPROGRAM_FLAGS) program $(ATPROGRAM_FLASH_FLAGS) --file $<

# Programs in the target EEPROM memory using ATPROGRAM
atprogram-ee: $(TARGET).elf $(MAKEFILE_LIST)
	@echo $(MSG_ATPROGRAM_CMD) Programming device \"$(MCU)\" EEPROM using \"$(ATPROGRAM_PROGRAMMER)\"
	atprogram $(BASE_ATPROGRAM_FLAGS) program $(ATPROGRAM_EEPROM_FLAGS) --file $<

# Phony build targets for this module
.PHONY: atprogram atprogram-ee
