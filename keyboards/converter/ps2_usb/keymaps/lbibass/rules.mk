# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = lite   # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE  = no  # Mouse keys(+4700)
EXTRAKEY_ENABLE  = yes  # Audio control and System control(+450)
CONSOLE_ENABLE   = yes  # Console for debug(+400)
COMMAND_ENABLE   = yes  # Commands for debug and configuration
NKRO_ENABLE      = yes  # USB Nkey Rollover
CUSTOM_MATRIX    = yes
PS2_USE_USART = yes

SRC = matrix.c
# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax
