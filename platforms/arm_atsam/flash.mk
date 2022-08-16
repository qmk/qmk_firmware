# Hey Emacs, this is a -*- makefile -*-
##############################################################################
# Architecture or project specific options
#

MDLOADER_CLI ?= mdloader

define EXEC_MDLOADER
	$(MDLOADER_CLI) --first --download $(BUILD_DIR)/$(TARGET).bin --restart
endef

mdloader: bin
	$(call EXEC_MDLOADER)

flash: bin
ifneq ($(strip $(PROGRAM_CMD)),)
	$(UNSYNC_OUTPUT_CMD) && $(PROGRAM_CMD)
else ifeq ($(strip $(ARM_ATSAM)),SAMD51J18A)
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_MDLOADER)
else
	$(PRINT_OK); $(SILENT) || printf "$(MSG_FLASH_ARCH)"
endif
