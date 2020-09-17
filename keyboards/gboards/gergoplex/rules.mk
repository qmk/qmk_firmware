MCU = atmega32u4

BOOTLOADER = atmel-dfu

CUSTOM_MATRIX    = yes
COMBO_ENABLE     = yes
EXTRAKEY_ENABLE  = yes
CONSOLE_ENABLE   = yes
COMMAND_ENABLE   = yes
BOOTMAGIC_ENABLE = lite

DEBOUNCE_TYPE  = eager_pr
SRC += matrix.c
QUANTUM_LIB_SRC += i2c_master.c
