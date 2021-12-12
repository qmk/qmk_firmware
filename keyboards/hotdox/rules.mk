# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options.
#
CUSTOM_MATRIX           = yes # Custom matrix file for the ErgoDone
UNICODE_ENABLE          = yes # Unicode
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE         = yes  # Mouse keys
EXTRAKEY_ENABLE         = yes # Audio control and System control
CONSOLE_ENABLE          = yes # Console for debug
COMMAND_ENABLE          = no  # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE        = yes # Enable keyboard backlight functionality
SWAP_HANDS_ENABLE       = no  # Disable Onehand
RGBLIGHT_ENABLE         = no

# project specific files
SRC =  matrix.c     \
	   i2c_master.c \
       left.c

LAYOUTS = ergodox
