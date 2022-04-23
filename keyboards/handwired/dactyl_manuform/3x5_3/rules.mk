# Build Options
# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = yes          # Audio output

RGB_MATRIX_ENABLE = yes     # Enable WS2812 RGB matrix
RGB_MATRIX_DRIVER = WS2812
SPLIT_KEYBOARD = yes

RGBLIGHT_SUPPORTED = yes
RGB_MATRIX_SUPPORTED = yes

LAYOUTS = split_3x5_3
