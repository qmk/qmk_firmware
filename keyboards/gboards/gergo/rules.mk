# Build Options
#   change yes to no to disable
#
CUSTOM_MATRIX 		= yes
EXTRAKEY_ENABLE		= yes
CONSOLE_ENABLE  	= yes
COMMAND_ENABLE		= yes
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite

SRC += matrix.c
QUANTUM_LIB_SRC += i2c_master.c
