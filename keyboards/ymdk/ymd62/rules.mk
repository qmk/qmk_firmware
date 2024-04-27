# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

# Configure for 128K flash
MCU_LDSCRIPT = STM32F103xB
