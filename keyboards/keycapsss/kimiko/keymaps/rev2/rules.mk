OLED_ENABLE = yes
OLED_DRIVER = SSD1306   # Enables the use of OLED displays

ENCODER_ENABLE = yes       # Enables the use of one or more encoders
ENCODER_MAP_ENABLE = yes

RGBLIGHT_ENABLE = no      # Enable keyboard 'old' RGB lightning
RGB_MATRIX_ENABLE = yes   # Enable keyboard RGB Matrix lightning

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pimoroni_trackball
# POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c

# LTO: Link Time Optimizations.
# Reduce compiled size, but will automatically disable the legacy TMK Macros and Functions features.
# This does not affect QMK Macros and Layers
LTO_ENABLE = yes