# MCU name
MCU = STM32F103
MCU_LDSCRIPT = stm32f103_bootloader
BOARD = ST_NUCLEO64_F103RB

# Bootloader selection
BOOTLOADER = custom

CUSTOM_MATRIX = yes

SRC += matrix.c
I2C_DRIVER_REQUIRED = yes
