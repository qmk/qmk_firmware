# MCU name
MCU = atmega32u4

# Processor frequency.
F_CPU = 16000000

# Target architecture (see library "Board Types" documentation).
ARCH = AVR8

# Input clock frequency.
F_USB = $(F_CPU)

# Bootloader
BOOTLOADER = qmk-dfu

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# Custom local font file
OPT_DEFS += -DOLED_FONT_H=\"common/glcdfont.c\"

SPLIT_KEYBOARD = yes
ENCODER_ENABLE = yes

DEFAULT_FOLDER = rgbkb/sol/rev2
