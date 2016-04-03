#
#            DMBS Build System
#     Released into the public domain.
#
#  dean [at] fourwalledcubicle [dot] com
#        www.fourwalledcubicle.com
#

DMBS_BUILD_MODULES         += AVRDUDE
DMBS_BUILD_TARGETS         += avrdude avrdude-ee
DMBS_BUILD_MANDATORY_VARS  += MCU TARGET
DMBS_BUILD_OPTIONAL_VARS   += AVRDUDE_PROGRAMMER AVRDUDE_PORT AVRDUDE_FLAGS AVRDUDE_MEMORY
DMBS_BUILD_PROVIDED_VARS   +=
DMBS_BUILD_PROVIDED_MACROS +=

# -----------------------------------------------------------------------------
#             DMBS AVRDUDE Programmer Buildsystem Makefile Module.
# -----------------------------------------------------------------------------
# DESCRIPTION:
#   Provides a set of targets to re-program a device using the open source
#   avr-dude utility.
# -----------------------------------------------------------------------------
# TARGETS:
#
#    avrdude                   - Program target FLASH with application using
#                                avrdude
#    avrdude-ee                - Program target EEPROM with application data
#                                using avrdude
#
# MANDATORY PARAMETERS:
#
#    MCU                       - Microcontroller device model name
#    TARGET                    - Application name
#
# OPTIONAL PARAMETERS:
#
#    AVRDUDE_PROGRAMMER        - Name of programming hardware to use
#    AVRDUDE_PORT              - Name of communication port to use
#    AVRDUDE_FLAGS             - Flags to pass to avr-dude
#    AVRDUDE_MEMORY            - Memory space to program application into (e.g.
#                                "application" for an XMEGA DFU device)
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
AVRDUDE_PROGRAMMER ?= jtagicemkii
AVRDUDE_PORT       ?= usb
AVRDUDE_FLAGS      ?=
AVRDUDE_MEMORY     ?= flash

# Sanity check user supplied values
$(foreach MANDATORY_VAR, $(DMBS_BUILD_MANDATORY_VARS), $(call ERROR_IF_UNSET, $(MANDATORY_VAR)))
$(call ERROR_IF_EMPTY, MCU)
$(call ERROR_IF_EMPTY, TARGET)
$(call ERROR_IF_EMPTY, AVRDUDE_PROGRAMMER)
$(call ERROR_IF_EMPTY, AVRDUDE_PORT)

# Output Messages
MSG_AVRDUDE_CMD    := ' [AVRDUDE] :'

# Construct base avrdude command flags
BASE_AVRDUDE_FLAGS := -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)

# Programs in the target FLASH memory using AVRDUDE
avrdude: $(TARGET).hex $(MAKEFILE_LIST)
	@echo $(MSG_AVRDUDE_CMD) Programming device \"$(MCU)\" FLASH using \"$(AVRDUDE_PROGRAMMER)\" on port \"$(AVRDUDE_PORT)\"
	avrdude $(BASE_AVRDUDE_FLAGS) -U $(AVRDUDE_MEMORY):w:$< $(AVRDUDE_FLAGS)

# Programs in the target EEPROM memory using AVRDUDE
avrdude-ee: $(TARGET).eep $(MAKEFILE_LIST)
	@echo $(MSG_AVRDUDE_CMD) Programming device \"$(MCU)\" EEPROM using \"$(AVRDUDE_PROGRAMMER)\" on port \"$(AVRDUDE_PORT)\"
	avrdude $(BASE_AVRDUDE_FLAGS) -U eeprom:w:$< $(AVRDUDE_FLAGS)

# Phony build targets for this module
.PHONY: $(DMBS_BUILD_TARGETS)
