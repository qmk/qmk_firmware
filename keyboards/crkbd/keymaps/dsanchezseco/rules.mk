
# If you want to change the display of OLED, you need to change here
SRC += ./logo_reader.c

# enable OLED displays
OLED_DRIVER_ENABLE = no

# enable media keys
EXTRAKEY_ENABLE = yes

# enable LEDs
RGB_MATRIX_ENABLE = WS2812

# using elite-c controllers
BOOTLOADER = qmk-dfu
