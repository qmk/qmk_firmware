# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control

# Debug options
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration

NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality

# RGB Options
#RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
#RGBLIGHT_ANIMATIONS = yes   # LED animations
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812

RGBLIGHT_SUPPORTED = yes
RGB_MATRIX_SUPPORTED = yes

AUDIO_ENABLE = no           # Audio output

# Encoders
ENCODER_ENABLE = no 		# Enable support for Rotary Encoder
EXTRA_ENCODERS_ENABLE = no  # Enables 3 encoders
