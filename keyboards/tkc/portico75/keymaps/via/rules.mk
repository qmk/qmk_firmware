VIA_ENABLE = yes
LTO_ENABLE = yes
RGB_MATRIX_ENABLE = no         # Use RGB matrix
ENCODER_MAP_ENABLE = yes

# project specific files
SRC += keyboards/wilba_tech/wt_main.c \
       keyboards/wilba_tech/wt_rgb_backlight.c \
       quantum/color.c \
       drivers/led/issi/is31fl3741.c

I2C_DRIVER_REQUIRED = yes
CIE1931_CURVE = yes
