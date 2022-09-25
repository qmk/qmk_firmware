# MCU name
MCU = RP2040

# Bootloader selection
BOOTLOADER = rp2040

# Build Options
#   change yes to no to disable
#
RGB_MATRIX_ENABLE = yes     # Enable keyboard RGB matrix (do not use together with RGBLIGHT_ENABLE)
RGB_MATRIX_DRIVER = WS2812  # RGB matrix driver support
WS2812_DRIVER = vendor
SPLIT_KEYBOARD = yes
LTO_ENABLE = yes

AUDIO_SUPPORTED = no
RGB_MATRIX_SUPPORTED = yes
#RGBLIGHT_ENABLE = yes
##BACKLIGHT_ENABLE = yes
SERIAL_DRIVER = vendor

LAYOUTS = split_3x5_3
OLED_DRIVER = SSD1306

 # Project specific files
#QUANTUM_LIB_SRC += spi_master.c
