ifeq ($(strip $(BOOTLOADER)), tinyuf2)
    MCU_LDSCRIPT = STM32F401xE
    EEPROM_DRIVER = vendor
    UF2_BUILD = yes
endif
