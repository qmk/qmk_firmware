# Build Options
#   change yes to no to disable
#
WS2812_DRIVER_REQUIRED = yes

COMMON_VPATH += $(DRIVER_PATH)/led/issi
SRC += is31fl3733.c
QUANTUM_LIB_SRC += i2c_master.c

LAYOUTS_HAS_RGB = yes
