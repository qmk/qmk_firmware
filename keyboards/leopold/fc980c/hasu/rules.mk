# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax

I2C_DRIVER_REQUIRED = yes

CUSTOM_MATRIX = yes
SRC += matrix.c keyboards/leopold/ad5258.c keyboards/leopold/actuation_point.c
