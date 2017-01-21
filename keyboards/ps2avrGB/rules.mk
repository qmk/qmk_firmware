# MCU name
MCU = atmega32a

PROTOCOL = VUSB

# disable UART since atmega32a apparently doesn't have it
NO_UART = yes
# this simplifies things for now
NO_SUSPEND_POWER_DOWN = yes

# Processor frequency.
#   Normally the first thing your program should do is set the clock prescaler,
#   so your program will run at the correct speed.  You should also set this
#   variable to same clock speed.  The _delay_ms() macro uses this, and many
#   examples use this variable to calculate timings.  Do not add a "UL" here.
F_CPU = 12000000

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes  # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes   # Mouse keys
EXTRAKEY_ENABLE = yes   # Audio control and System control
CONSOLE_ENABLE = yes    # Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
#BACKLIGHT_ENABLE = yes

# V-USB debug level: To use ps2_usart.c level must be 0
# ps2_usart.c requires USART to receive PS/2 signal.
OPT_DEFS = -DDEBUG_LEVEL=0
OPS_DEFS += -DPROTOCOL_VUSB
OPT_DEFS += -DBOOTLOADER_SIZE=2048

CUSTOM_MATRIX = yes
SRC = matrix.c

#---------------- Programming Options --------------------------
PROGRAM_CMD = ./keyboards/ps2avrGB/program $(TARGET).hex
