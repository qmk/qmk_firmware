SRC = TWIlib.c issi.c lighting.c

MCU = atmega32u4
OPT_DEFS += -DBOOTLOADER_SIZE=4096

F_CPU = 16000000
F_USB = $(F_CPU)
ARCH = AVR8

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

LAYOUTS = numpad_6x4
