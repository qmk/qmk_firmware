# Common feature for all keyboards
BOOTMAGIC_ENABLE  = yes
EXTRAKEY_ENABLE   = yes
TAP_DANCE_ENABLE  = yes
MACROS_ENABLED    = yes
RGBLIGHT_ENABLE   = no
RGB_MATRIX_ENABLE = no

# Keyboard specific
BOOTMAGIC_ENABLE      = yes       # Enable Bootmagic Lite
EXTRAKEY_ENABLE       = yes       # Audio control and System control
TAP_DANCE_ENABLE      = yes       # Tap Dance keys
NKRO_ENABLE           = yes       # Enable N-Key Rollover
MACROS_ENABLED        = yes

AUTO_SHIFT_ENABLE     = no 
CONSOLE_ENABLE        = no        # Console for debug
COMMAND_ENABLE        = no        # Commands for debug and configuration
BACKLIGHT_ENABLE      = no        # Enable keyboard backlight functionality
RGBLIGHT_ENABLE       = no        # Enable keyboard RGB underglow
AUDIO_ENABLE          = no        # Audio output
MOUSEKEY_ENABLE       = no        # Mouse keys

RGB_MATRIX_ENABLE     = yes
RGB_MATRIX_DRIVER     = WS2812
WS2812_DRIVER         = vendor
ENCODER_ENABLE        = yes
ENCODER_MAP_ENABLE    = yes
OLED_ENABLE           = yes
OLED_DRIVER           = SSD1306