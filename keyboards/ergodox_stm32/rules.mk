# custom bootloader
MCU_LDSCRIPT = stm32f103_bootloader
BOARD = ST_NUCLEO64_F103RB

CUSTOM_MATRIX = yes

SRC += matrix.c
I2C_DRIVER_REQUIRED = yes
