# only uncomment on the side you have your trackball on
POINTING_DEVICE_ENABLE = yes
SRC += drivers/sensors/pimoroni_trackball.c
I2C_MASTER_DRIVER_REQUIRED := yes
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
MOUSEKEY_ENABLE = no
