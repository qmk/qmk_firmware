SRC += bootloader.c

PROGRAM_CMD = hyisp-util flash --convert --yes $(BUILD_DIR)/$(TARGET).bin

MCU_FAMILY = NUMICRO
MCU_SERIES = NUC123

MCU_LDSCRIPT = NUC123xD4xx0

MCU_STARTUP = NUC123

ARMV = 6
