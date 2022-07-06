MOUSEKEY_ENABLE   = yes    # Mouse keys
RGBLIGHT_ENABLE   = no
RGB_MATRIX_ENABLE = yes
OLED_ENABLE       = yes
OLED_DRIVER       = SSD1306
LTO_ENABLE        = yes
BOOTLOADER        = atmel-dfu

SRC += ./oled.c ./rgb.c
