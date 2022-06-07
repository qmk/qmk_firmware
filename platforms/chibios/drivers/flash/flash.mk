# Hey Emacs, this is a -*- makefile -*-
##############################################################################
# Architecture or project specific options
#

DFU_ARGS ?=
ifneq ("$(SERIAL)","")
	DFU_ARGS += -S $(SERIAL)
endif

DFU_UTIL ?= dfu-util

define EXEC_DFU_UTIL
	if ! $(DFU_UTIL) -l | grep -q "Found DFU"; then \
		printf "$(MSG_BOOTLOADER_NOT_FOUND_QUICK_RETRY)" ;\
		sleep $(BOOTLOADER_RETRY_TIME) ;\
		while ! $(DFU_UTIL) -l | grep -q "Found DFU"; do \
			printf "." ;\
			sleep $(BOOTLOADER_RETRY_TIME) ;\
		done ;\
		printf "\n" ;\
	fi
	$(DFU_UTIL) $(DFU_ARGS) -D $(BUILD_DIR)/$(TARGET).bin
endef


define EXEC_WB32_DFU_UPDATER
	if ! wb32-dfu-updater_cli -l | grep -q "Found DFU"; then \
		printf "$(MSG_BOOTLOADER_NOT_FOUND_QUICK_RETRY)" ;\
		sleep $(BOOTLOADER_RETRY_TIME) ;\
		while ! wb32-dfu-updater_cli -l | grep -q "Found DFU"; do \
			printf "." ;\
			sleep $(BOOTLOADER_RETRY_TIME) ;\
		done ;\
		printf "\n" ;\
	fi
	wb32-dfu-updater_cli -D $(BUILD_DIR)/$(TARGET).bin
endef

dfu-util: $(BUILD_DIR)/$(TARGET).bin cpfirmware sizeafter
	$(call EXEC_DFU_UTIL)

define EXEC_UF2_UTIL_DEPLOY
	if ! $(UF2CONV) --deploy $(BUILD_DIR)/$(TARGET).uf2 2>/dev/null; then \
		printf "$(MSG_BOOTLOADER_NOT_FOUND_QUICK_RETRY)" ;\
		sleep $(BOOTLOADER_RETRY_TIME) ;\
		while ! $(UF2CONV) --deploy $(BUILD_DIR)/$(TARGET).uf2  2>/dev/null; do \
			printf "." ;\
			sleep $(BOOTLOADER_RETRY_TIME) ;\
		done ;\
		printf "\n" ;\
	fi
endef

# TODO: Remove once ARM has a way to configure EECONFIG_HANDEDNESS
#       within the emulated eeprom via dfu-util or another tool
ifneq (,$(filter $(MAKECMDGOALS), dfu-util-split-left uf2-split-left))
    OPT_DEFS += -DINIT_EE_HANDS_LEFT
endif

ifneq (,$(filter $(MAKECMDGOALS), dfu-util-split-right uf2-split-right))
    OPT_DEFS += -DINIT_EE_HANDS_RIGHT
endif

dfu-util-split-left: dfu-util

dfu-util-split-right: dfu-util

uf2-split-left: flash

uf2-split-right: flash

ST_LINK_CLI ?= st-link_cli
ST_LINK_ARGS ?=

st-link-cli: $(BUILD_DIR)/$(TARGET).hex sizeafter
	$(ST_LINK_CLI) $(ST_LINK_ARGS) -q -c SWD -p $(BUILD_DIR)/$(TARGET).hex -Rst

ST_FLASH ?= st-flash
ST_FLASH_ARGS ?=

st-flash: $(BUILD_DIR)/$(TARGET).hex sizeafter
	$(ST_FLASH) $(ST_FLASH_ARGS) --reset --format ihex write $(BUILD_DIR)/$(TARGET).hex

# Autodetect teensy loader
ifndef TEENSY_LOADER_CLI
    ifneq (, $(shell which teensy-loader-cli 2>/dev/null))
        TEENSY_LOADER_CLI ?= teensy-loader-cli
    else
        TEENSY_LOADER_CLI ?= teensy_loader_cli
    endif
endif

TEENSY_LOADER_CLI_MCU ?= $(MCU_LDSCRIPT)

define EXEC_TEENSY
	$(TEENSY_LOADER_CLI) -mmcu=$(TEENSY_LOADER_CLI_MCU) -w -v $(BUILD_DIR)/$(TARGET).hex
endef

teensy: $(BUILD_DIR)/$(TARGET).hex cpfirmware sizeafter
	$(call EXEC_TEENSY)


flash: $(BUILD_DIR)/$(TARGET).bin cpfirmware sizeafter
ifneq ($(strip $(PROGRAM_CMD)),)
	$(UNSYNC_OUTPUT_CMD) && $(PROGRAM_CMD)
else ifeq ($(strip $(BOOTLOADER)),kiibohd)
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_DFU_UTIL)
else ifeq ($(strip $(BOOTLOADER)),tinyuf2)
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_UF2_UTIL_DEPLOY)
else ifeq ($(strip $(MCU_FAMILY)),KINETIS)
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_TEENSY)
else ifeq ($(strip $(MCU_FAMILY)),MIMXRT1062)
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_TEENSY)
else ifeq ($(strip $(MCU_FAMILY)),STM32)
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_DFU_UTIL)
else ifeq ($(strip $(MCU_FAMILY)),WB32)
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_WB32_DFU_UPDATER)
else ifeq ($(strip $(MCU_FAMILY)),GD32V)
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_DFU_UTIL)
else
	$(PRINT_OK); $(SILENT) || printf "$(MSG_FLASH_BOOTLOADER)"
endif
