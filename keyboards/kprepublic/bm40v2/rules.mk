# MCU name
MCU = atmega32u4

# VIA
VIA_ENABLE = yes

# Bootloader selection
BOOTLOADER = atmel-dfu

IGNORE_MOD_TAP_INTERRUPT = yes
HOLD_ON_OTHER_KEY_PRESS = no

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = custom
RGB_MATRIX_CUSTOM_USER = yes
WS2812_DRIVER_REQUIRED = yes
LTO_ENABLE = yes

COMMON_VPATH += $(DRIVER_PATH)/led/issi
SRC += is31fl3733.c
QUANTUM_LIB_SRC += i2c_master.c

LAYOUTS_HAS_RGB = yes
