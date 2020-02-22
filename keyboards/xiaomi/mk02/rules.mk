# MCU name
MCU = STM32F072
BOARD = ST_STM32F072B_DISCOVERY
MCU_LDSCRIPT = STM32F072_0x2000_bootloader

DFU_ARGS = -d 0483:df11 -a 0 -s 0x08002000:leave
DFU_SUFFIX_ARGS = -v 0483 -p DF11

BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = no	# Mouse keys
EXTRAKEY_ENABLE = no	# Audio control and System control
CONSOLE_ENABLE = no	# Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = no	    # USB Nkey Rollover
CUSTOM_MATRIX = no # Custom matrix file
# BACKLIGHT_ENABLE = yes # This is broken on 072 for some reason
RGBLIGHT_ENABLE = no
