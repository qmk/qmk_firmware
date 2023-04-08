# Build Options
#   change yes to no to disable
#
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = spi_flash

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

# Ultrafast custom matrix scanning code
CUSTOM_MATRIX = lite
SRC += matrix.c

GRAVE_ESC_ENABLE = no #No need for this feature because keyboard has F row and dedicated escape button
