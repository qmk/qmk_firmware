# MCU name

MCU = atmega32a

WS2812_DRIVER = bitbang

# Processor frequency
F_CPU = 16000000

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = USBasp

# Custom local font file
OPT_DEFS += -DOLED_FONT_H=\"common/glcdfont.c\"

ENCODER_ENABLE = yes

DEFAULT_FOLDER = rgbkb/pan/rev1
