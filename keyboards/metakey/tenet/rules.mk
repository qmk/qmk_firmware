MCU = cortex-m0plus
ARMV = 6
USE_FPU = no
MCU_FAMILY = HT32
MCU_SERIES = HT32F523xx
MCU_LDSCRIPT = HT32F52352_TENET
MCU_STARTUP = ht32f523xx

BOARD = METAKEY_TENET

BOOTLOADER = custom
PROGRAM_CMD = hexcore_flash --device tenet-70 --boot $(BUILD_DIR)/$(TARGET).bin

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
WS2812_DRIVER = custom

CUSTOM_MATRIX = lite
SRC = \
    matrix.c \
    ws2812_custom.c \
    ssd1326.c
