EEPROM_DRIVER = i2c

POINTING_DEVICE_ENABLE = yes
SRC += drivers/sensors/pimoroni_trackball.c
I2C_MASTER_DRIVER_REQUIRED := yes
