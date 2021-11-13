
#DEFAULT_FOLDER = 40percentclub/polyandry/promicro #Unused for now. Divide all the Promicro specific files into their own folder. See i75 for examples on how to do this.
MCU = atmega32u4
BOOTLOADER = caterina
BOOTMAGIC_ENABLE = lite	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes	# Mouse keys(+4700)
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes	
SLEEP_LED_ENABLE = no
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = no