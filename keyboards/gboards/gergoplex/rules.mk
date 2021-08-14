MCU = atmega32u4

BOOTLOADER = atmel-dfu

CUSTOM_MATRIX    = yes
MOUSEKEY_ENABLE  = yes  # Mouse keys
COMBO_ENABLE     = yes
EXTRAKEY_ENABLE  = yes
CONSOLE_ENABLE   = no
NKRO_ENABLE      = yes  # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
COMMAND_ENABLE   = yes
BOOTMAGIC_ENABLE = lite

LAYOUTS = split_3x5_3

DEBOUNCE_TYPE = sym_eager_pr
SRC += matrix.c
QUANTUM_LIB_SRC += i2c_master.c
