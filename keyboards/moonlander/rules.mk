#Cortex version
MCU  = STM32F303

#Build Options
#comment out to disable the options.
#
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = lite # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes   # Mouse keys
EXTRAKEY_ENABLE = yes   # Audio control and System control
CONSOLE_ENABLE = no     # Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
#SLEEP_LED_ENABLE = yes #Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	    # USB Nkey Rollover
CUSTOM_MATRIX = yes # Custom matrix file
AUDIO_ENABLE = yes
SWAP_HANDS_ENABLE = no
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = IS31FL3731
#SERIAL_LINK_ENABLE = yes
EEPROM_DRIVER      = i2c

#project specific files
SRC = matrix.c
QUANTUM_LIB_SRC += i2c_master.c

MOUSE_SHARED_EP = no
