#
#             LUFA Library
#     Copyright (C) Dean Camera, 2015.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

LUFA_BUILD_MODULES         += DFU
LUFA_BUILD_TARGETS         += flip flip-ee dfu dfu-ee
LUFA_BUILD_MANDATORY_VARS  += MCU TARGET
LUFA_BUILD_OPTIONAL_VARS   +=
LUFA_BUILD_PROVIDED_VARS   +=
LUFA_BUILD_PROVIDED_MACROS +=

# -----------------------------------------------------------------------------
#               LUFA DFU Bootloader Buildsystem Makefile Module.
# -----------------------------------------------------------------------------
# DESCRIPTION:
#   Provides a set of targets to re-program a device currently running a DFU
#   class bootloader with a project's FLASH and EEPROM files.
# -----------------------------------------------------------------------------
# TARGETS:
#
#    flip                      - Program FLASH into target via Atmel FLIP
#    flip-ee                   - Program EEPROM into target via Atmel FLIP
#    dfu                       - Program FLASH into target via dfu-programmer
#    dfu-ee                    - Program EEPROM into target via dfu-programmer
#
# MANDATORY PARAMETERS:
#
#    MCU                       - Microcontroller device model name
#    TARGET                    - Application name
#
# OPTIONAL PARAMETERS:
#
#    (None)
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

# Sanity-check values of mandatory user-supplied variables
$(foreach MANDATORY_VAR, $(LUFA_BUILD_MANDATORY_VARS), $(call ERROR_IF_UNSET, $(MANDATORY_VAR)))
$(call ERROR_IF_EMPTY, MCU)
$(call ERROR_IF_EMPTY, TARGET)

# Output Messages
MSG_COPY_CMD   := ' [CP]      :'
MSG_REMOVE_CMD := ' [RM]      :'
MSG_DFU_CMD    := ' [DFU]     :'

# Programs in the target FLASH memory using BATCHISP, the command line tool used by FLIP
flip: $(TARGET).hex $(MAKEFILE_LIST)
	@echo $(MSG_DFU_CMD) Programming FLASH with batchisp using \"$<\"
	batchisp -hardware usb -device $(MCU) -operation erase f loadbuffer $< program
	batchisp -hardware usb -device $(MCU) -operation start reset 0

# Programs in the target EEPROM memory using BATCHISP, the command line tool used by FLIP
flip-ee: $(TARGET).eep $(MAKEFILE_LIST)
	@echo $(MSG_COPY_CMD) Copying EEP file to temporary file \"$<.hex\"
	cp $< $<.hex
	@echo $(MSG_DFU_CMD) Programming EEPROM with batchisp using \"$<.hex\"
	batchisp -hardware usb -device $(MCU) -operation memory EEPROM loadbuffer $<.hex program
	batchisp -hardware usb -device $(MCU) -operation start reset 0
	@echo $(MSG_REMOVE_CMD) Removing temporary file \"$<.hex\"
	rm $<.hex

# Programs in the target FLASH memory using DFU-PROGRAMMER
dfu: $(TARGET).hex $(MAKEFILE_LIST)
	@echo $(MSG_DFU_CMD) Programming FLASH with dfu-programmer using \"$<\"
	dfu-programmer $(MCU) erase
	dfu-programmer $(MCU) flash $<
	dfu-programmer $(MCU) reset

# Programs in the target EEPROM memory using DFU-PROGRAMMER
dfu-ee: $(TARGET).eep $(MAKEFILE_LIST)
	@echo $(MSG_DFU_CMD) Programming EEPROM with dfu-programmer using \"$<\"
	dfu-programmer $(MCU) flash --eeprom $<
	dfu-programmer $(MCU) reset

# Phony build targets for this module
.PHONY: flip flip-ee dfu dfu-ee
