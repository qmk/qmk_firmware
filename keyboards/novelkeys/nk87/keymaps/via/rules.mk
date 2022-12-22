
# Build Options
#   chagne yes to no to disable
#
VIA_ENABLE = yes

RGB_MATRIX_ENABLE = no            # Use RGB matrix. This must be set to no for this keymap since it uses RGB_BACKLIGHT_* by default.

# project specific files
SRC =	keyboards/wilba_tech/wt_main.c \
		keyboards/wilba_tech/wt_rgb_backlight.c \
		drivers/led/issi/is31fl3733.c \
		quantum/color.c \
		i2c_master.c