# MCU Name
MCU = STM32F072

BOARD = ST_STM32F072B_DISCOVERY

# Build Options
# 	change yes to no to disable
#	change no to yes to enable
#
BOOTMAGIC_ENABLE = no		# Virtual DIP switch configuration
MOUSEKEY_ENABLE = no		# Mouse Functionality
EXTRAKEY_ENABLE = yes		# Audio Control and System Controls
CONSOLE_ENABLE = no			# Console for Debugging
COMMAND_ENABLE = no			# Commands for Debugging and Configuration
SLEEP_LED_ENABLE = no		# Breating Sleep LED during USB Suspend
NKRO_ENABLE = no 			# USB NKey Rollover | If this doesn't work, see here:  https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = no		# Enable keyboard backlight functionality
BLUETOOTH_ENABLE = no       # Enable Bluetooth
AUDIO_ENABLE = no           # Audio output

WS2812_DRIVER = bitbang
RGB_MATRIX_ENABLE = WS2812

OLED_DRIVER_ENABLE = yes
