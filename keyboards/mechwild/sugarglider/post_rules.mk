ifeq ($(strip $(BOOTLOADER)), tinyuf2)
    ifndef EEPROM_DRIVER
        MCU_LDSCRIPT = STM32F401xE
        EEPROM_DRIVER = vendor
        UF2_BUILD = yes
    endif
endif

# Checking if WIDE_OLED
ifeq ($(strip $(WIDE_OLED_ENABLE)), yes)
    OPT_DEFS += -DOLED_DISPLAY_128X64
endif
