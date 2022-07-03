# MCU name
MCU = STM32F103

# Bootloader selection
BOOTLOADER = stm32duino

CONSOLE_ENABLE = yes

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
