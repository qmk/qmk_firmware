# MCU name
MCU = STM32F072

# Build Options
#   comment out to disable the options.
#

SRC += led.c \
      satisfaction_encoder.c \
      satisfaction_oled.c

#BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	    # USB Nkey Rollover
CUSTOM_MATRIX = no # Custom matrix file
ENCODER_ENABLE = yes
QWIIC_ENABLE += MICRO_OLED
#BACKLIGHT_ENABLE = yes

DEFAULT_FOLDER = cannonkeys/satisfaction75/rev1
