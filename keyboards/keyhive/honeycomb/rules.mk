# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
#MOUSEKEY_ENABLE = yes	# Mouse keys
POINTING_DEVICE_ENABLE = yes # Generic Pointer, not as big as mouse keys hopefully.
POINTING_DEVICE_DRIVER = custom
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes   # Commands for debug and configuration
CUSTOM_MATRIX = yes    # Remote matrix from the wireless bridge
NKRO_ENABLE = yes           # Enable N-Key Rollover
# BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality

# # project specific files
SRC += matrix.c
UART_DRIVER_REQUIRED = yes
