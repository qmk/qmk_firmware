MCU = atmega32u4

# Bootloader selection
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu: You can redefine 'bootloader exit' key and LED pin in config.h
#   atmega32a    bootloadHID
BOOTLOADER = lufa-dfu

FIRMWARE_FORMAT = hex