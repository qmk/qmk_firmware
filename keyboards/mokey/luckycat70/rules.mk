MCU = STM32F103

# Wear-levelling driver
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = embedded_flash

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

# Wildcard to allow APM32 MCU
DFU_SUFFIX_ARGS = -p FFFF -v FFFF
