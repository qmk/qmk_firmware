ENCODER_MAP_ENABLE = yes
VIA_ENABLE = yes
VIAL_ENABLE = yes
ENCODER_ENABLE = yes
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog
BACKLIGHT_ENABLE = yes
BACKLIGHT_DRIVER = software
OLED_ENABLE = yes
OPT_DEFS += -DHAL_USE_I2C=TRUE
BOOTMAGIC_ENABLE = yes
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = analog_joystick
#OLED_DRIVER = ssd1306
#OLED_TRANSPORT = i2c
#OPT_DEFS += -DHAL_USE_I2C=TRUE
 # OLED SSD1306 128x32
#ifeq ($(strip $(OLED_ENABLE)), yes)
# OLED_DRIVER_ENABLE = yes
#endif