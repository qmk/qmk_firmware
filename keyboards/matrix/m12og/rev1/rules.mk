# MCU name
MCU = STM32F103

MCU_LDSCRIPT = m12og_v1

BOARD = m12og_v1

# Bootloader selection
BOOTLOADER = custom

CUSTOM_MATRIX = lite
SRC += matrix.c
