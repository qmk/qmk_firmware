# MCU name
MCU = STM32F072
BOARD = ST_STM32F072B_DISCOVERY

# Build Options
#   comment out to disable the options.
#

# project specific files
#VPATH += keyboards/cannonkeys/stm32f072
#SRC +=	keyboards/cannonkeys/stm32f072/keyboard.c  \
# 		keyboards/cannonkeys/stm32f072/led.c

BOOTMAGIC_ENABLE = lite	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = no	# Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	    # USB Nkey Rollover
CUSTOM_MATRIX = no # Custom matrix file
#BACKLIGHT_ENABLE = yes # This is broken on 072 for some reason
BACKLIGHT_ENABLE = yes
RGBLIGHT_ENABLE = yes
WS2812_DRIVER = spi
LEADER_ENABLE = no
FAUXCLICKY_ENABLE = no
MIDI_ENABLE = no
BLUETOOTH_ENABLE = no
KEY_LOCK_ENABLE = no
TERMINAL_ENABLE = no
OLED_DRIVER_ENABLE = yes

# LAYOUTS = ext65
