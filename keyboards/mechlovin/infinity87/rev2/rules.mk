# MCU name
MCU = atmega32a

# processor frequency
F_CPU = 16000000

# Bootloader
BOOTLOADER = bootloadHID

# Build Options
#   change yes to no to disable
#

CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no           # USB Nkey Rollover
BACKLIGHT_ENABLE  = yes     # Enable keyboard backlight functionality
CUSTOM_MATRIX = yes

SRC += matrix.c
