# MCU name
MCU = atmega32a

# Bootloader selection
BOOTLOADER = bootloadhid

# build options
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = yes
BACKLIGHT_ENABLE = yes
RGBLIGHT_ENABLE = yes
WS2812_DRIVER = i2c

LAYOUTS = 65_ansi_blocker 65_iso_blocker
