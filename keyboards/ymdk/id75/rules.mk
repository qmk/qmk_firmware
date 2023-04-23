# Configure for 128K flash
#MCU_LDSCRIPT = STM32F103xB

# Wildcard to allow APM32 MCU
DFU_SUFFIX_ARGS = -p FFFF -v FFFF

WS2812_DRIVER = pwm
# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
