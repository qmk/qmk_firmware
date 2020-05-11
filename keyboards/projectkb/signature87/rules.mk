# MCU name
MCU = STM32F072
# Build Options
#   comment out to disable the options.
#
#BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	    # USB Nkey Rollover
# BACKLIGHT_ENABLE = yes # This is broken on 072 for some reason

LAYOUTS = tkl_ansi
