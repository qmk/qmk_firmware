# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches

EEPROM_DRIVER = i2c

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = custom

COMMON_VPATH += $(DRIVER_PATH)/issi
SRC += drivers/led/issi/is31fl3741.c

LTO_ENABLE = yes
OPT = 2
