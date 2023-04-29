# Bootloader selection
MCU_LDSCRIPT = STM32F103xC

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

# Wear-levelling driver
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = spi_flash
