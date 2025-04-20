# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      	# Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes      		# Mouse keys
EXTRAKEY_ENABLE = yes			# Audio control and System control
CONSOLE_ENABLE = yes            # Console for debug
COMMAND_ENABLE = yes            # Commands for debug and configuration
NKRO_ENABLE = no                # Enable N-Key Rollover
BACKLIGHT_ENABLE = no           # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes	        # Enable keyboard RGB underglow
AUDIO_ENABLE = no               # Audio output
SPLIT_KEYBOARD = yes			# Keyboard has two controllers
ENCODER_ENABLE = yes 			# Encoder Functionality Enabled
ENCODER_MAP_ENABLE = yes 		# Ability to use Keymap with encoder
LTO_ENABLE = no 				# Optimise
OLED_ENABLE = yes				# OLED Display
POINTING_DEVICE_ENABLE = yes 	# Trackball or Trackpad
VIA_ENABLE = yes  				# VIA
WS2812_DRIVER_REQUIRED = yes

POINTING_DEVICE_DRIVER = pmw3389
SERIAL_DRIVER = vendor
WS2812_DRIVER = vendor
OLED_DRIVER = ssd1306
OLED_TRANSPORT = i2c
BOARD = GENERIC_RP_RP2040


# If you want to change the display of OLED, you need to change here
 SRC += ./lib/layer_state_reader.c \
		./lib/keylogger.c \
        ./lib/logo_reader.c \
        ./lib/mode_icon_reader.c \
		./lib/rgb_state_reader.c \
        ./lib/host_led_state_reader.c \
        ./lib/timelogger.c \

