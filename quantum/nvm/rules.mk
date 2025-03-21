# Copyright 2024 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later

VPATH += $(QUANTUM_DIR)/nvm

VALID_NVM_DRIVERS := eeprom custom none

NVM_DRIVER ?= eeprom

ifeq ($(filter $(NVM_DRIVER),$(VALID_NVM_DRIVERS)),)
    $(call CATASTROPHIC_ERROR,Invalid NVM_DRIVER,NVM_DRIVER="$(NVM_DRIVER)" is not a valid NVM driver)
else

    # If we don't want one, fake it with transient eeprom.
    ifeq ($(NVM_DRIVER),none)
        NVM_DRIVER := eeprom
        EEPROM_DRIVER := transient
    endif

    NVM_DRIVER_UPPER := $(shell echo $(NVM_DRIVER) | tr '[:lower:]' '[:upper:]')
    NVM_DRIVER_LOWER := $(shell echo $(NVM_DRIVER) | tr '[:upper:]' '[:lower:]')

    OPT_DEFS += -DNVM_DRIVER_$(NVM_DRIVER_UPPER) -DNVM_DRIVER="$(NVM_DRIVER)"

    ifneq ("$(wildcard $(QUANTUM_DIR)/nvm/$(NVM_DRIVER_LOWER))","")
        COMMON_VPATH += $(QUANTUM_DIR)/nvm/$(NVM_DRIVER_LOWER)
    endif

    QUANTUM_SRC += nvm_eeconfig.c

endif
