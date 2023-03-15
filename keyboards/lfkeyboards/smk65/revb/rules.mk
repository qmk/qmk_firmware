# Build Options
#   change yes to no to disable
#
BACKLIGHT_ENABLE = no           # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no            # Enable keyboard RGB underglow
RGBLIGHT_CUSTOM_DRIVER = yes    # RGB code is implemented in lefkeyboards, not WS2812
AUDIO_ENABLE = no               # Audio output

# Extra source files for IS3731 lighting
SRC += TWIlib.c issi.c lighting.c
