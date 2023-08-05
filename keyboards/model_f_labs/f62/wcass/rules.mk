# Build Options
#   change yes to no to disable
#
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
RAW_ENABLE = yes
HAPTIC_ENABLE = yes
HAPTIC_DRIVER = SOLENOID
CUSTOM_MATRIX=lite
SRC += ../xwhatsit_capsense_matrix.c ../xwhatsit_util_comm.c
