#
#            DMBS Build System
#     Released into the public domain.
#
#  dean [at] fourwalledcubicle [dot] com
#        www.fourwalledcubicle.com
#

DMBS_BUILD_MODULES         += ATPROGRAM
DMBS_BUILD_TARGETS         += atprogram atprogram-ee
DMBS_BUILD_MANDATORY_VARS  += MCU TARGET
DMBS_BUILD_OPTIONAL_VARS   += ATPROGRAM_PROGRAMMER ATPROGRAM_INTERFACE ATPROGRAM_PORT
DMBS_BUILD_PROVIDED_VARS   +=
DMBS_BUILD_PROVIDED_MACROS +=

# Conditionally import the CORE module of DMBS if it is not already imported
DMBS_MODULE_PATH := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
ifeq ($(findstring CORE, $(DMBS_BUILD_MODULES)),)
  include $(DMBS_MODULE_PATH)/core.mk
endif

# Default values of optionally user-supplied variables
ATPROGRAM_PROGRAMMER ?= atmelice
ATPROGRAM_INTERFACE  ?= jtag
ATPROGRAM_PORT       ?=

# Sanity check user supplied values
$(foreach MANDATORY_VAR, $(DMBS_BUILD_MANDATORY_VARS), $(call ERROR_IF_UNSET, $(MANDATORY_VAR)))
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
.PHONY: $(DMBS_BUILD_TARGETS)
