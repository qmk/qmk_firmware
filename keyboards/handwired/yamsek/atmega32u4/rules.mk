# MCU name
MCU = atmega32u4
BOOTLOADER = caterina

RGBLIGHT_ENABLE = no
RGBLIGHT_DRIVER = WS2812

POINTING_DEVICE_ENABLE = no
POINTING_DEVICE_DRIVER = pimoroni_trackball

## saving space to squeeze in VIAL support
# (by explicitly disabeling features, some of which might be auto-enabled by the build scripts)
AUTO_SHIFT_ENABLE = no
COMBO_ENABLE = no
DEBUG_ENABLE = no
#  KEY_OVERRIDE_ENABLE            = yes              # file
#  OLED_DRIVER                    = SSD1306          # file
#  RAW_ENABLE                     = yes              # file
TAP_DANCE_ENABLE = no

