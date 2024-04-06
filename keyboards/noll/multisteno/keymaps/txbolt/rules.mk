# MCU name
MCU = STM32F103

# Bootloader selection
BOOTLOADER = stm32duino

# project specific files
SRC =	keyboard.c

BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = no	# Mouse keys
EXTRAKEY_ENABLE = no	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	    # USB Nkey Rollover
COMBO_ENABLE = yes		# Enable Key Combos
STENO_ENABLE = yes		# Stenography keys
STENO_PROTOCOL = txbolt	# geminipr or txbolt
MOUSEKEY_ENABLE = no	# Mouse keys