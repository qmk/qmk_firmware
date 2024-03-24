BOOTMAGIC_ENABLE = no   # Enable Bootmagic Lite
MOUSEKEY_ENABLE  = no   # Mouse keys
EXTRAKEY_ENABLE  = yes  # Audio control and System control
CONSOLE_ENABLE   = yes  # Console for debug
COMMAND_ENABLE   = no   # Commands for debug and configuration
CUSTOM_MATRIX    = yes  # Custom matrix file for the ErgoDox Extended
NKRO_ENABLE      = yes  # Enable N-Key Rollover
UNICODE_ENABLE   = yes  # Unicode

# project specific files
SRC += matrix.c
I2C_DRIVER_REQUIRED = yes
