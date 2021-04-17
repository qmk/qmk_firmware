# only uncomment on the side you have your trackball on
PIMORONI_TRACKBALL_ENABLE = yes

ifeq ($(strip $(PIMORONI_TRACKBALL_ENABLE)), yes)
    POINTING_DEVICE_ENABLE = yes
    SRC += pimoroni_trackball.c
    QUANTUM_LIB_SRC += i2c_master.c
	OLED_DRIVER_ENABLE = yes
	MOUSEKEY_ENABLE = no
endif
