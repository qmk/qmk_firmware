# MCU name
MCU = atmega32a

# Bootloader selection
BOOTLOADER = bootloadhid

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
BACKLIGHT_ENABLE = yes
RGBLIGHT_ENABLE = no  # PCB has underglow LEDs, but case doesn't let them show.
WS2812_DRIVER = i2c

LAYOUTS = ortho_6x4 numpad_6x4
