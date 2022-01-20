# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes		# Bootmagic Lite
MOUSEKEY_ENABLE = yes		# Mouse keys
EXTRAKEY_ENABLE = yes		# Audio control and System control
CONSOLE_ENABLE = no			# Console for debug
COMMAND_ENABLE = no			# Commands for debug and configuration
NKRO_ENABLE = yes			# N-Key Rollover
BACKLIGHT_ENABLE = no		# Keyboard backlight functionality
RGBLIGHT_ENABLE = no		# Keyboard RGB underglow
RGB_MATRIX_ENABLE = yes		# RGB matrix effects
RGB_MATRIX_DRIVER = WS2812	# RGB matrix driver
LTO_ENABLE = yes			# Link time optimization
AUDIO_ENABLE = no			# Audio output
DYNAMIC_MACRO_ENABLE = yes	# Macro recording in realtime
ENCODER_ENABLE = yes		# Encoder