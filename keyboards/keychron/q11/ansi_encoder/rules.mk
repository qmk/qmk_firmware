# Build Options
#   change yes to no to disable
#
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = embedded_flash
SERIAL_DRIVER = usart

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
