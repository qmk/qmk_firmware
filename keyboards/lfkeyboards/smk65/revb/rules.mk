# Build Options
#   change yes to no to disable
#
BACKLIGHT_ENABLE = no           # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no            # Enable keyboard RGB underglow
AUDIO_ENABLE = no               # Audio output

# Extra source files for IS3731 lighting
SRC += TWIlib.c issi.c lighting.c
