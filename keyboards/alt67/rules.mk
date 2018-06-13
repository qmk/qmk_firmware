# project specific files
SRC = led_programs.c
SRC += matrix.c

#For platform and packs
ARM_ATSAM = SAMD51J18A
MCU = cortex-m4

CUSTOM_MATRIX = yes

# Build Options
#   comment out to disable the options.
#
#MOUSEKEY_ENABLE = yes   # Mouse keys
EXTRAKEY_ENABLE = yes   # Audio control and System control
#CONSOLE_ENABLE = yes    # Console for debug (enables debug prints to virtser, no console support)
NKRO_ENABLE = yes       # USB Nkey Rollover
#VIRTSER_ENABLE = yes    # USB Serial Driver
#RAW_ENABLE = yes
