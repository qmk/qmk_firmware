# MCU name
MCU = atmega32u4

# Processor frequency
F_CPU = 8000000

# Bootloader selection
BOOTLOADER = lufa-ms
BOOTLOADER_SIZE = 6144

# Build Options
#   change yes to no to disable
#
CUSTOM_MATRIX           = yes # Custom matrix file
UNICODE_ENABLE          = yes # Unicode
BOOTMAGIC_ENABLE        = yes # Enable Bootmagic Lite
MOUSEKEY_ENABLE         = yes # Mouse keys
EXTRAKEY_ENABLE         = yes # Audio control and System control
CONSOLE_ENABLE          = no  # Console for debug
COMMAND_ENABLE          = no  # Commands for debug and configuration
NKRO_ENABLE             = yes # Enable N-Key Rollover
BACKLIGHT_ENABLE        = no  # Enable keyboard backlight functionality
SWAP_HANDS_ENABLE       = no  # Disable Onehand
RGBLIGHT_ENABLE         = no

# project specific files
SRC = \
    led.c      \
    matrix.c   \
    
