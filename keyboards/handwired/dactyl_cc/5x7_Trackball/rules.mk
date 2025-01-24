# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes		# Audio control and System control
CONSOLE_ENABLE = no             # Console for debug
COMMAND_ENABLE = no             # Commands for debug and configuration
NKRO_ENABLE = no                # Enable N-Key Rollover
BACKLIGHT_ENABLE = no           # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no	        # Enable keyboard RGB underglow
AUDIO_ENABLE = no               # Audio output
SPLIT_KEYBOARD = yes			# Keyboard has two controllers
ENCODER_ENABLE = no				# Encoder Functionality Enabled
ENCODER_MAP_ENABLE = no			# Ability to use Keymap with encoder
LTO_ENABLE = no 				# Optimise
OLED_ENABLE = no				# OLED Display
POINTING_DEVICE_ENABLE = yes 	# Trackball or Trackpad

POINTING_DEVICE_DRIVER = pmw3389
SERIAL_DRIVER = vendor
WS2812_DRIVER = vendor
BOARD = GENERIC_RP_RP2040
