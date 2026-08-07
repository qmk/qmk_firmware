# Do not put the microcontroller into power saving mode
# when we get USB suspend event. We want it to keep updating
# backlight effects.
NO_SUSPEND_POWER_DOWN = yes

CIE1931_CURVE = yes
I2C_DRIVER_REQUIRED = yes

# project specific files
SRC =	keyboards/wilba_tech/wt_main.c \
		keyboards/wilba_tech/wt_rgb_backlight.c \
		quantum/color.c \
		drivers/led/issi/is31fl3218.c
