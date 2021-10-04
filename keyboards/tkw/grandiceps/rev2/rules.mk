EEPROM_DRIVER = i2c

POINTING_DEVICE_ENABLE = yes
SRC += drivers/sensors/pimoroni_trackball.c
QUANTUM_LIB_SRC += i2c_master.c
