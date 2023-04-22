# MCU name
MCU = atmega32u4
F_CPU = 8000000
ARCH = AVR8
F_USB = $(F_CPU)
# Interrupt driven control endpoint task(+60)
#OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# Feather uses the caterina bootloader
#OPT_DEFS += -DBOOTLOADER_SIZE=4096

OS_DETECTION_ENABLE = yes

CUSTOM_MATRIX = yes          # We have a custom matrix
SRC += matrix.c sx1509.c proxsense.cpp i2c.c

