PIMORONI_TRACKBALL_ENABLE = yes
ifeq ($(strip $(PIMORONI_TRACKBALL_ENABLE)), yes)
    POINTING_DEVICE_ENABLE = yes
    SRC += drivers/sensors/pimoroni_trackball.c
    OPT_DEFS += -DPIMORONI_TRACKBALL_ENABLE
    OPT_DEFS += -DPIMORONI_TRACKBALL_CLICK
#orientation pimoroni text on top and trackball text at the bottom
    OPT_DEFS += -DPIMORONI_TRACKBALL_ROTATE
    OPT_DEFS += -DPIMORONI_TRACKBALL_INVERT_X
    QUANTUM_LIB_SRC += i2c_master.c
endif

OLED_ENABLE = yes
