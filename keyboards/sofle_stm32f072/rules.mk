# MCU name
MCU = STM32F072

# Bootloader selection
BOOTLOADER = stm32-dfu

# Wildcard to allow APM32 MCU
DFU_SUFFIX_ARGS = -v FFFF -p FFFF

SPLIT_KEYBOARD = yes
DEFAULT_FOLDER = sofle_stm32f072/rev1
SWAP_HANDS_ENABLE = yes


NKRO_ENABLE = yes           # Enable N-Key Rollover
LTO_ENABLE = yes

