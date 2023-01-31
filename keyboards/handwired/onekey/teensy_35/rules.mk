# MCU name
MCU = MK64FX512

# Bootloader selection
BOOTLOADER = halfkay

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
