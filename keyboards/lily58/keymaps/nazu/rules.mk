EXTRAKEY_ENABLE = yes

# flags for OLED
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
WPM_ENABLE = yes

# RBG
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB light
RGB_MATRIX_ENABLE = no
RGB_MATRIX_DRIVER = WS2812

ENCODER_ENABLE = no       # Enables the use of one or more encoders
# BACKLIGHT_ENABLE = yes     # Enable keyboard backlight functionality
LINK_TIME_OPTIMIZATION_ENABLE = yes 	   # significantly reduce the compiled size, but disable the legacy TMK Macros and Functions features
TAP_DANCE_ENABLE = yes	  # Enable Tap Dance

NKRO_ENABLE = yes            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work

EXTRAFLAGS += -flto
MOUSEKEY_ENABLE = no
