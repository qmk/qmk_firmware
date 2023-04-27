# Wildcard to allow APM32 MCU
DFU_SUFFIX_ARGS = -v FFFF -p FFFF
NO_USB_STARTUP_CHECK = yes
# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
