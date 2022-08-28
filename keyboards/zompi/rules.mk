# MCU name
MCU = RP2040

# Bootloader selection
BOOTLOADER = rp2040

# Build Options
#   change yes to no to disable
#
RGB_MATRIX_ENABLE = no     # Enable keyboard RGB matrix (do not use together with RGBLIGHT_ENABLE)
#RGB_MATRIX_DRIVER = WS2812  # RGB matrix driver support
SPLIT_KEYBOARD = yes
LTO_ENABLE = yes

AUDIO_SUPPORTED = no
RGB_MATRIX_SUPPORTED = no
RGBLIGHT_SUPPORTED = no
SERIAL_DRIVER = vendor

LAYOUTS = split_3x5_3
OLED_DRIVER = SSD1306

