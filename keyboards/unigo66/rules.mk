# MCU name
MCU = atmega32u4


F_CPU ?= 16000000

DEFAULT_FOLDER = UniGo66

ARCH = AVR8

F_USB = $(F_CPU)


BOOTLOADER = caterina

# Interrupt driven control endpoint task
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

USB_HID_ENABLE = yes

CUSTOM_MATRIX = yes
SRC = custom_matrix.cpp
