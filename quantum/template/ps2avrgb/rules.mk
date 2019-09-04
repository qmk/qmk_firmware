# MCU name
MCU = atmega32a

# Bootloader
#     This definition is optional, and if your keyboard supports multiple bootloaders of
#     different sizes, comment this out, and the correct address will be loaded
#     automatically (+60). See bootloader.mk for all options.
BOOTLOADER = bootloadHID

# build options
BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = yes
COMMAND_ENABLE = yes
BACKLIGHT_ENABLE = no
RGBLIGHT_ENABLE = yes
RGBLIGHT_CUSTOM_DRIVER = yes

OPT_DEFS = -DDEBUG_LEVEL=0

SRC += i2c_master.c
