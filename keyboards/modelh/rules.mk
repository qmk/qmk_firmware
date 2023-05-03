# MCU name
MCU = STM32F103

BOOTLOADER = stm32duino

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

CUSTOM_MATRIX = no 	# Custom matrix file
