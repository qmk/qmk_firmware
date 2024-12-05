# Bootloader selection
# Cannot use `BOOTLOADER = stm32duino` due to the need to override
# `MCU_LDSCRIPT`, therefore all parameters need to be specified here manually.
OPT_DEFS += -DBOOTLOADER_STM32DUINO
MCU_LDSCRIPT = STM32F103x6_stm32duino
BOOTLOADER_TYPE = stm32duino
DFU_ARGS = -d 1EAF:0003 -a 2 -R
DFU_SUFFIX_ARGS = -v 1EAF -p 0003

# EEPROM emulation not supported yet (need to implement a proper firmware size
# check first, otherwise the chance of the EEPROM backing store overwriting
# some part of the firmware code is really high).
EEPROM_DRIVER = transient
