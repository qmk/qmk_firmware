# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

OLED_ENABLE = yes
OLED_DRIVER = SSD1306   # Enables the use of OLED displays
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = yes     # Enable keyboard RGB matrix (do not use together with RGBLIGHT_ENABLE)
RGB_MATRIX_DRIVER = WS2812 # RGB matrix driver support
RGB_MATRIX_SUPPORTED = yes
