# MCU name
MCU = STM32F303

# Build Options
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = no	  # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no	  # Mouse keys
EXTRAKEY_ENABLE = yes	  # Audio control and System control
CONSOLE_ENABLE = no	  # Console for debug
COMMAND_ENABLE = no     # Commands for debug and configuration
NKRO_ENABLE = no	      # USB Nkey Rollover
AUDIO_ENABLE = no

# project specific files
SRC =	led.c
# LAYOUTS += layout_1 layout_2
