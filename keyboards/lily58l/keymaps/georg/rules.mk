OLED_DRIVER_ENABLE = yes   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = no       # Enable keyboard RGB light
RGB_MATRIX_ENABLE = WS2812
WPM_ENABLE = no
MOUSEKEY_ENABLE = no      # Mouse keys
# CONSOLE_ENABLE = yes 
SRC += oled.c encoder.c macros.c settings.c

# uncomment to the line to customize the setting
#define ENCODER_DIRECTION_FLIP # Switch encoder’s directions
#define ENCODER_RESOLUTION 4 # Tune encoder resolution
