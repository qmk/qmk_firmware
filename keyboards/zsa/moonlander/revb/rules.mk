CUSTOM_MATRIX = lite

VPATH += drivers/gpio
SRC += matrix.c mcp23018.c
I2C_DRIVER_REQUIRED = yes

MCU_LDSCRIPT = moonlander

DFU_ARGS = -d 3297:2003 -a 0 -s 0x08002000:leave
DFU_SUFFIX_ARGS = -v 3297 -p 2003