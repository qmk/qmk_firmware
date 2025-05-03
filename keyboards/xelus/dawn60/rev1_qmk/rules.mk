# Do not put the microcontroller into power saving mode
# when we get USB suspend event. We want it to keep updating
# backlight effects.
NO_SUSPEND_POWER_DOWN = yes

I2C_DRIVER_REQUIRED = yes
WS2812_DRIVER_REQUIRED = yes

# project specific files
COMMON_VPATH += $(DRIVER_PATH)/issi
SRC +=  drivers/led/issi/is31fl3731.c
