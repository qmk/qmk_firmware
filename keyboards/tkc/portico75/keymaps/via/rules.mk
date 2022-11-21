VIA_ENABLE = yes
LTO_ENABLE = yes
RGB_MATRIX_ENABLE = no         # Use RGB matrix

# project specific files
SRC += keyboards/wilba_tech/wt_main.c \
       keyboards/wilba_tech/wt_rgb_backlight.c \
       quantum/color.c \
       drivers/led/issi/is31fl3741.c

QUANTUM_LIB_SRC += i2c_master.c
