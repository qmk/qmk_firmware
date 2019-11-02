# MCU name
MCU = atmega32a

# Bootloader
#     This definition is optional, and if your keyboard supports multiple bootloaders of
#     different sizes, comment this out, and the correct address will be loaded
#     automatically (+60). See bootloader.mk for all options.
BOOTLOADER = bootloadHID

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
WS2812_DRIVER = i2c

OPT_DEFS = -DDEBUG_LEVEL=0
