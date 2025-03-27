# custom bootloader
MCU_LDSCRIPT = abelx_boot
BOARD = abelx_bd

CUSTOM_MATRIX = lite
# project specific files
SRC += matrix.c tca6424.c aw9523b.c
I2C_DRIVER_REQUIRED = yes
WS2812_DRIVER_REQUIRED = yes
