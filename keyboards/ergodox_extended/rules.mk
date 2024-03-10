BOOTMAGIC_ENABLE = no   # Enable Bootmagic Lite
MOUSEKEY_ENABLE  = yes  # Mouse keys
EXTRAKEY_ENABLE  = yes  # Audio control and System control
CONSOLE_ENABLE   = yes  # Console for debug
COMMAND_ENABLE   = no   # Commands for debug and configuration
CUSTOM_MATRIX    = lite # Custom matrix file for the ErgoDox EZ
NKRO_ENABLE      = yes           # Enable N-Key Rollover
UNICODE_ENABLE   = no  # Unicode
SWAP_HANDS_ENABLE= no   # Allow swapping hands of keyboard

# project specific files
SRC += matrix.c
I2C_DRIVER_REQUIRED = yes

# Disable unsupported hardware
AUDIO_SUPPORTED = no
BACKLIGHT_SUPPORTED = no

MOUSE_SHARED_EP = no
