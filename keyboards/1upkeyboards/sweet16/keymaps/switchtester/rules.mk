# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no  # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no   # Mouse keys
EXTRAKEY_ENABLE = yes  # Audio control and System control
CONSOLE_ENABLE = yes   # Console for debug
COMMAND_ENABLE = yes   # Commands for debug and configuration
NKRO_ENABLE = no       # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = no

SRC += switches.c
