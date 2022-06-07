# MCU name
MCU = atmega32u4

BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes     # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # USB Nkey Rollover
BACKLIGHT_ENABLE = no 	    # Enable keyboard backlight functionality on B7 by default
RGBLIGHT_ENABLE = no      # Enable WS2812 RGB underlight. - We have custom RGB underglow
ENCODER_ENABLE = yes		# For Knob support
