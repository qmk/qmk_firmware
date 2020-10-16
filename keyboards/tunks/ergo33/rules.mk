# MCU name
MCU = atmega32u4

# Interrupt driven control endpoint task(+60)
# OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

BOOTLOADER = atmel-dfu

# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 1024
#   Atmel DFU loader 4096
#   LUFA bootloader  4096
#   USBaspLoader     2048
# OPT_DEFS += -DBOOTLOADER_SIZE=4096

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = lite     # Virtual DIP switch configuration
#COMBO_ENABLE = yes          # Key combos
#COMMAND_ENABLE = yes        # Commands for debug and configuration
#CONSOLE_ENABLE = yes        # Console for debug
ENCODER_ENABLE = yes        # Rotary encoders
EXTRAKEY_ENABLE = yes	      # Audio control and System control
MOUSEKEY_ENABLE = yes       # Mouse keys
NKRO_ENABLE = yes		        # USB Nkey Rollover - if this doesn't work, see: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = yes       # Enable keyboard underlight functionality
#UNICODE_ENABLE = yes        # Unicode characters
