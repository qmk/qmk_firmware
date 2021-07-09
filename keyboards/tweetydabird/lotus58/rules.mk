# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
BOOTMAGIC_ENABLE = lite     # Virtual DIP switch configuration
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration

NKRO_ENABLE = yes            # USB Nkey Rollover
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow

ENCODER_ENABLE = yes
OLED_DRIVER_ENABLE = yes
TAP_DANCE_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
SPLIT_KEYBOARD = yes