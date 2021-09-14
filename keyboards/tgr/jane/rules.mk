# MCU name
MCU = atmega32a

# Bootloader selection
BOOTLOADER = bootloadhid

# build options
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = yes
BACKLIGHT_ENABLE = yes
RGBLIGHT_ENABLE = no
WS2812_DRIVER = i2c

LAYOUTS = tkl_ansi tkl_iso
