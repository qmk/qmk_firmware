# GENERIC STM32F103C8T6 board - stm32duino bootloader
# MCU NAME
MCU=STM32F103
BOOTLOADER =  stm32duino
WS2812_DRIVER = bitbang

# GENERIC STM32F103C8T6 board - stm32duino bootloader
OPT_DEFS = -DCORTEX_ENABLE_WFI_IDLE=TRUE
## Chibi options that should no longer be needed. 
##-DCORTEX_VTOR_INIT=0x2000
# Options to pass to dfu-util when flashing
##DFU_ARGS = -d 1EAF:0003 -a 2 -R
##DFU_SUFFIX_ARGS  ?= -v 1EAF -p 0003

# avoid warning about LTO & ChibiOS, even though it mostly works
#LTO_ENABLE = no

