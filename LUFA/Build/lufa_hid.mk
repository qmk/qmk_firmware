#
#             LUFA Library
#     Copyright (C) Dean Camera, 2013.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

LUFA_BUILD_MODULES         += HID
LUFA_BUILD_TARGETS         += hid hid-ee teensy teensy-ee
LUFA_BUILD_MANDATORY_VARS  += MCU TARGET
LUFA_BUILD_OPTIONAL_VARS   += 
LUFA_BUILD_PROVIDED_VARS   += 
LUFA_BUILD_PROVIDED_MACROS += 

# -----------------------------------------------------------------------------
#               LUFA HID Bootloader Buildsystem Makefile Module.
# -----------------------------------------------------------------------------
# DESCRIPTION:
#   Provides a set of targets to re-program a device currently running a HID
#   class bootloader with a project's FLASH files.
# -----------------------------------------------------------------------------
# TARGETS:
#
#    hid                       - Program FLASH into target via
#                                hid_bootloader_cli
#    hid-ee                    - Program EEPROM into target via a temporary
#                                AVR application and hid_bootloader_cli
#    teensy                    - Program FLASH into target via
#                                teensy_loader_cli
#    teensy-ee                 - Program EEPROM into target via a temporary
#                                AVR application and teensy_loader_cli
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
MSG_HID_BOOTLOADER_CMD := ' [HID]     :'
MSG_OBJCPY_CMD         := ' [OBJCPY]  :'
MSG_MAKE_CMD           := ' [MAKE]    :'

# Programs in the target FLASH memory using the HID_BOOTLOADER_CLI tool
hid: $(TARGET).hex $(MAKEFILE_LIST)
	@echo $(MSG_HID_BOOTLOADER_CMD) Programming FLASH with hid_bootloader_cli using \"$<\"
	hid_bootloader_cli -mmcu=$(MCU) -v $<

# Programs in the target EEPROM memory using the HID_BOOTLOADER_CLI tool (note: clears target FLASH memory)
hid-ee: $(TARGET).eep $(MAKEFILE_LIST)
	@echo $(MSG_OBJCPY_CMD) Converting \"$<\" to a binary file \"InputEEData.bin\"
	avr-objcopy -I ihex -O binary $< $(patsubst %/,%,$(LUFA_PATH))/Build/HID_EEPROM_Loader/InputEEData.bin
	@echo $(MSG_MAKE_CMD) Making EEPROM loader application for \"$<\"
	make -C $(patsubst %/,%,$(LUFA_PATH))/Build/HID_EEPROM_Loader/ MCU=$(MCU) clean hid

# Programs in the target FLASH memory using the TEENSY_BOOTLOADER_CLI tool
teensy: $(TARGET).hex $(MAKEFILE_LIST)
	@echo $(MSG_HID_BOOTLOADER_CMD) Programming FLASH with teensy_loader_cli using \"$<\"
	teensy_loader_cli -mmcu=$(MCU) -v $<

# Programs in the target EEPROM memory using the TEENSY_BOOTLOADER_CLI tool (note: clears target FLASH memory)
teensy-ee: $(TARGET).hex $(MAKEFILE_LIST)
	@echo $(MSG_OBJCPY_CMD) Converting \"$<\" to a binary file \"InputEEData.bin\"
	avr-objcopy -I ihex -O binary $< $(patsubst %/,%,$(LUFA_PATH))/Build/HID_EEPROM_Loader/InputEEData.bin
	@echo $(MSG_MAKE_CMD) Making EEPROM loader application for \"$<\"
	make -s -C $(patsubst %/,%,$(LUFA_PATH))/Build/HID_EEPROM_Loader/ MCU=$(MCU) clean hid-teensy
	
# Phony build targets for this module
.PHONY: hid hid-ee teensy teensy-ee
