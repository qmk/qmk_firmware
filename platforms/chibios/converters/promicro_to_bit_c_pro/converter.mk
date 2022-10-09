# nullbits Bit-C PRO MCU settings for converting AVR projects
MCU := RP2040
BOARD := QMK_PM2040
BOOTLOADER := rp2040

# These are defaults based on what has been implemented for RP2040 boards
SERIAL_DRIVER ?= vendor
WS2812_DRIVER ?= vendor
BACKLIGHT_DRIVER ?= software

# Tell QMK to use the correct 2nd stage bootloader
OPT_DEFS += -DRP2040_FLASH_W25X10CL
