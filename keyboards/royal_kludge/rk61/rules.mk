# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

DFU_SUFFIX_ARGS = -p FFFF -v FFFF