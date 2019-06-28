# MCU name
MCU = STM32F103

# bluepill (with stm32duino bootloader) overrides
OPT_DEFS = -DCORTEX_VTOR_INIT=0x2000
MCU_LDSCRIPT = STM32F103x8_stm32duino_bootloader
DFU_ARGS = -d 1eaf:0003 -a2 -R
DFU_SUFFIX_ARGS ?= -v 1eaf -p 0003
