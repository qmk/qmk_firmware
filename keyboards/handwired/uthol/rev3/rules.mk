# MCU name
MCU = STM32F401

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes
NKRO_ENABLE = yes
KEYBOARD_SHARED_EP = yes
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
WPM_ENABLE = yes
EXTRAKEY_ENABLE = yes
ENCODER_ENABLE = yes
RGBLIGHT_ENABLE = yes
RGBLIGHT_DRIVER = WS2812
