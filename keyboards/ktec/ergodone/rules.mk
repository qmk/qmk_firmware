# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   comment out to disable the options.
#
CUSTOM_MATRIX           = yes # Custom matrix file for the ErgoDone
UNICODE_ENABLE          = yes # Unicode
BOOTMAGIC_ENABLE        = yes # Enable Bootmagic Lite
MOUSEKEY_ENABLE         = yes # Mouse keys
EXTRAKEY_ENABLE         = yes # Audio control and System control
CONSOLE_ENABLE          = no  # Console for debug
COMMAND_ENABLE          = no  # Commands for debug and configuration
SLEEP_LED_ENABLE        = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE             = yes # USB Nkey Rollover - not yet supported in LUFA
USB_6KRO_ENABLE         = no  # USB 6key Rollover
BACKLIGHT_ENABLE        = no  # Enable keyboard backlight functionality
SWAP_HANDS_ENABLE       = no  # Disable Onehand
RGBLIGHT_ENABLE         = no

# project specific files
QUANTUM_LIB_SRC += i2c_master.c
SRC = \
    matrix.c   \
    expander.c \

LAYOUTS = ergodox
