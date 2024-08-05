# The custom RGB Matrix driver combines IS31FL3733 and WS2812; things that are
# normally done by common_features.mk for both of these drivers need to be done
# here manually.
COMMON_VPATH += $(DRIVER_PATH)/led/issi
SRC += is31fl3733.c
I2C_DRIVER_REQUIRED = yes
WS2812_DRIVER_REQUIRED = yes
