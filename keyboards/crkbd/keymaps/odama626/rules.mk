MOUSEKEY_ENABLE = no    # Mouse keys
RGBLIGHT_ENABLE = no    # Enable WS2812 RGB underlight.


# RGB_MATRIX_ENABLE = yes


OLED_ENABLE     = yes
OLED_DRIVER     = SSD1306
LTO_ENABLE      = yes
CAPS_WORD_ENABLE = yes
BOOTLOADER=qmk-dfu
EXTRAFLAGS+=-flto


VPATH  +=  keyboards/gboards/
COMBO_ENABLE   = yes
WPM_ENABLE = yes
