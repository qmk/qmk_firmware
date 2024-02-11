MCU_FAMILY = MIMXRT1062
MCU_SERIES = MIMXRT1062
MCU_LDSCRIPT = MIMXRT1062
MCU_STARTUP = MIMXRT1062
BOARD = IC_TEENSY_4_1
MCU = cortex-m4
ARMV = 7

# Bootloader selection
BOOTLOADER = halfkay

FIRMWARE_FORMAT = hex

# Do not enter lower-power sleep mode when on the ChibiOS idle thread.
# See https://github.com/qmk/qmk_firmware/issues/23053.
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=FALSE
