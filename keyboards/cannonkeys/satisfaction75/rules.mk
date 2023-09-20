# Wildcard to allow APM32 MCU
DFU_SUFFIX_ARGS = -v FFFF -p FFFF

VPATH += keyboards/cannonkeys/lib/satisfaction75
SRC += satisfaction_encoder.c \
      satisfaction_oled.c \
      satisfaction_core.c 

OLED_DRIVER = ssd1306

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

DEFAULT_FOLDER = cannonkeys/satisfaction75/rev1