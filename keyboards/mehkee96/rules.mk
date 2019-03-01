# MCU name
MCU = atmega32a
PROTOCOL = VUSB

# unsupported features for now
NO_UART = yes
NO_SUSPEND_POWER_DOWN = yes

# Processor frequency.
F_CPU = 12000000

# Bootloader
BOOTLOADER = bootloadHID


# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes	# Mouse keys(+4700)
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = yes	# Console for debug(+400)
COMMAND_ENABLE = yes    # Commands for debug and configuration
BACKLIGHT_ENABLE = no  # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes
RGBLIGHT_CUSTOM_DRIVER = yes

OPT_DEFS = -DDEBUG_LEVEL=0

# custom matrix setup
CUSTOM_MATRIX = yes
SRC = matrix.c i2c.c

# programming options
PROGRAM_CMD = ./keyboards/mehkee96/program $(TARGET).hex
