# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes      # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover

CUSTOM_MATRIX = yes
QUANTUM_LIB_SRC += i2c_master.c
SRC += leds.c \
	   matrix.c

# You can set RGB_MATRIX_ENABLE = no in your rules.mk to disable this and save the Flash
RGB_MATRIX_ENABLE = yes # Enable RGB matrix effects.
RGB_MATRIX_DRIVER = custom
