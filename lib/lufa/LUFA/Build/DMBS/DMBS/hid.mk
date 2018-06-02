#
#            DMBS Build System
#     Released into the public domain.
#
#  dean [at] fourwalledcubicle [dot] com
#        www.fourwalledcubicle.com
#

DMBS_BUILD_MODULES         += HID
DMBS_BUILD_TARGETS         += hid hid-ee teensy teensy-ee
DMBS_BUILD_MANDATORY_VARS  += MCU TARGET
DMBS_BUILD_OPTIONAL_VARS   +=
DMBS_BUILD_PROVIDED_VARS   +=
DMBS_BUILD_PROVIDED_MACROS +=

# Conditionally import the CORE module of DMBS if it is not already imported
DMBS_MODULE_PATH := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
ifeq ($(findstring CORE, $(DMBS_BUILD_MODULES)),)
  include $(DMBS_MODULE_PATH)/core.mk
endif

# Sanity-check values of mandatory user-supplied variables
$(foreach MANDATORY_VAR, $(DMBS_BUILD_MANDATORY_VARS), $(call ERROR_IF_UNSET, $(MANDATORY_VAR)))
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
	avr-objcopy -I ihex -O binary $< $(DMBS_MODULE_PATH)/HID_EEPROM_Loader/InputEEData.bin
	@echo $(MSG_MAKE_CMD) Making EEPROM loader application for \"$<\"
	$(MAKE) -C $(DMBS_MODULE_PATH)/HID_EEPROM_Loader/ MCU=$(MCU) clean hid

# Programs in the target FLASH memory using the TEENSY_BOOTLOADER_CLI tool
teensy: $(TARGET).hex $(MAKEFILE_LIST)
	@echo $(MSG_HID_BOOTLOADER_CMD) Programming FLASH with teensy_loader_cli using \"$<\"
	teensy_loader_cli -mmcu=$(MCU) -v $<

# Programs in the target EEPROM memory using the TEENSY_BOOTLOADER_CLI tool (note: clears target FLASH memory)
teensy-ee: $(TARGET).hex $(MAKEFILE_LIST)
	@echo $(MSG_OBJCPY_CMD) Converting \"$<\" to a binary file \"InputEEData.bin\"
	avr-objcopy -I ihex -O binary $< $(DMBS_MODULE_PATH)/HID_EEPROM_Loader/InputEEData.bin
	@echo $(MSG_MAKE_CMD) Making EEPROM loader application for \"$<\"
	$(MAKE) -s -C $(DMBS_MODULE_PATH)/HID_EEPROM_Loader/ MCU=$(MCU) clean teensy

# Phony build targets for this module
.PHONY: $(DMBS_BUILD_TARGETS)
