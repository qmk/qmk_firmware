# Wildcard to allow APM32 MCU
DFU_SUFFIX_ARGS = -v FFFF -p FFFF

VPATH += keyboards/cannonkeys/lib/satisfaction75
SRC += lib/satisfaction75/satisfaction_encoder.c \
      lib/satisfaction75/satisfaction_oled.c \
      lib/satisfaction75/satisfaction75_core.c 

# Build Options
#   change yes to no to disable
#
OLED_ENABLE = yes
OLED_DRIVER = SSD1306

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
