# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu

NKRO_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
RGBLIGHT_ENABLE = yes

DEFAULT_FOLDER = mechllama/g35/v2
