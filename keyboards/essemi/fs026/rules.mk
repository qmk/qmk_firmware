# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=FALSE

# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = FS026

#EEPROM_DRIVER = custom
