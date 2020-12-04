# MCU name
MCU = STM32F303

# LED Configuration
LED_MATRIX_ENABLE = yes
LED_MATRIX_DRIVER = IS31FL3731

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration
## (Note that for BOOTMAGIC on Teensy LC you have to use a custom .ld script.)
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
#SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	    # USB Nkey Rollover
#CUSTOM_MATRIX = yes # Custom matrix file
AUDIO_ENABLE = yes
# SERIAL_LINK_ENABLE = yes

# project specific files
SRC =	led.c
LAYOUTS = 66_ansi
