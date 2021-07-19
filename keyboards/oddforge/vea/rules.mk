# MCU name
MCU = atmega32a
BOOTLOADER = bootloadHID

# Build Options
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
WS2812_DRIVER = i2c

# custom matrix setup
CUSTOM_MATRIX = lite
SRC = matrix.c
QUANTUM_LIB_SRC += i2c_master.c
