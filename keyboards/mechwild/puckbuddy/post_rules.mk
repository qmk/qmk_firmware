ifeq ($(strip $(BOOTLOADER)), tinyuf2)
    ifndef EEPROM_DRIVER
        MCU_LDSCRIPT = STM32F401xE
        EEPROM_DRIVER = vendor
        UF2_BUILD = yes
    endif
endif