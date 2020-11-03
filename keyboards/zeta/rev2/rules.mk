
OPT_DEFS += -DZETA_PROMICRO


# # project specific files
SRC = matrix.c
MCU = atmega32u4

BOOTLOADER = caterina

# Build Options
#   comment out to disable the options.

BOOTMAGIC_ENABLE = lite   # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes     # Mouse keys
EXTRAKEY_ENABLE = yes     # Audio control and System control
CONSOLE_ENABLE = no       # Console for debug
COMMAND_ENABLE = yes      # Commands for debug and configuration
CUSTOM_MATRIX = yes       # Remote matrix from the wireless bridge
NKRO_ENABLE = yes         # USB Nkey Rollover 
BACKLIGHT_ENABLE = no     # Enable keyboard backlight functionality
UNICODE_ENABLE = yes      # Unicode
BLUETOOTH_ENABLE = no     # Enable Bluetooth 

USB = /dev/ttyACM0

# upload: build
# 	$(ZETA_UPLOAD_COMMAND)

LAYOUTS = ortho_4x12
