#
#            DMBS Build System
#     Released into the public domain.
#
#  dean [at] fourwalledcubicle [dot] com
#        www.fourwalledcubicle.com
#

DMBS_BUILD_MODULES         += DFU
DMBS_BUILD_TARGETS         += flip flip-ee dfu dfu-ee
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
.PHONY: $(DMBS_BUILD_TARGETS)
