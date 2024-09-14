# custom bootloader
MCU_LDSCRIPT = noah_boot
BOARD = ST_NUCLEO64_F411RE

WS2812_DRIVER_REQUIRED = yes

CUSTOM_MATRIX = yes
# project specific files
SRC += matrix.c
