# custom bootloader
MCU_LDSCRIPT = m20add_boot
BOARD = ST_NUCLEO64_F411RE

CUSTOM_MATRIX = lite
# project specific files
SRC += matrix.c tca6424.c rgb_ring.c drivers/led/issi/is31fl3731.c
I2C_DRIVER_REQUIRED = yes
