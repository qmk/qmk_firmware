# MCU name
MCU = STM32F103

# Bootloader selection
# Cannot use `BOOTLOADER = stm32duino` due to the need to override
# `MCU_LDSCRIPT`, therefore all parameters need to be specified here manually.
OPT_DEFS += -DBOOTLOADER_STM32DUINO
MCU_LDSCRIPT = STM32F103x6_stm32duino_bootloader
BOARD = STM32_F103_STM32DUINO
BOOTLOADER_TYPE = stm32duino
DFU_ARGS = -d 1EAF:0003 -a 2 -R
DFU_SUFFIX_ARGS = -v 1EAF -p 0003

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

# LTO is required to fit the firmware into the available 24K of flash
LTO_ENABLE = yes

# Disable some features which still don't fit into flash even with LTO
MOUSEKEY_ENABLE = no
NKRO_ENABLE = no

# EEPROM emulation not supported yet (need to implement a proper firmware size
# check first, otherwise the chance of the EEPROM backing store overwriting
# some part of the firmware code is really high).
EEPROM_DRIVER = transient
