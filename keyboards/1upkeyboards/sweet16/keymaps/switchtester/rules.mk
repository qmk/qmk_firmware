# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no  # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no   # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes  # Audio control and System control(+450)
CONSOLE_ENABLE = yes   # Console for debug(+400)
COMMAND_ENABLE = yes   # Commands for debug and configuration
NKRO_ENABLE = no       # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = no

SRC += switches.c
