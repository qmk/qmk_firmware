# MCU name
MCU = STM32F303

# Build Options
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = no	  # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes	  # Mouse keys
EXTRAKEY_ENABLE = yes	  # Audio control and System control
CONSOLE_ENABLE = yes	  # Console for debug
COMMAND_ENABLE = no     # Commands for debug and configuration
NKRO_ENABLE = yes	      # USB Nkey Rollover
AUDIO_ENABLE = yes

# project specific files
SRC =	led.c
LAYOUTS += 60_ansi 60_ansi_split_bs_rshift 60_iso
