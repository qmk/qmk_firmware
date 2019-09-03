
# If you want to change the display of OLED, you need to change here
SRC += ./logo_reader.c

# enable OLED displays
OLED_DRIVER_ENABLE = yes

# enable media keys
EXTRAKEY_ENABLE = yes

# enable LEDs
RGBLIGHT_ENABLE = yes

# using elite-c controllers
BOOTLOADER = qmk-dfu
