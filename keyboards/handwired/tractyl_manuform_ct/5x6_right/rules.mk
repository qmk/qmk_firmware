# Hardware/build options
#DEFAULT_FOLDER 			= handwired/tractyl_manuform_ct/5x6_right
MCU 					= atmega32u4	# MCU name
BOOTLOADER 				= atmel-dfu		# Bootloader selection

# Functionality options
CONSOLE_ENABLE			= no        # Debugging things, takes up flash dependent of what you have turned on; w. rgb, 4.8k, w/o rgb, 2.7k
MOUSEKEY_ENABLE 		= yes       # Mouse keys
EXTRAKEY_ENABLE 		= no       # Audio control and System control, 400 bytes
NKRO_ENABLE 			= no 		# saves 300 bytes when no, trying to keep it off       # Enable N-Key Rollover
TAP_DANCE_ENABLE        = yes		# temp disabling for troubleshooting

# LED config - rgb matrix uses 3.8k of flash
# to toggle rgb, set both to yes or no
RGB_MATRIX_ENABLE 		= yes # this to 'no' didn't turn off the custom colours; rgb_matrix:yes/custom_rgb:no = no custom colours
CUSTOM_RGB_MATRIX       = yes # this to 'no' turned everything off
RGB_MATRIX_DRIVER 		= WS2812

# Trackball settings
POINTING_DEVICE_ENABLE 	= yes
POINTING_DEVICE_DRIVER 	= pmw3360
MOUSE_SHARED_EP 		= yes 		# doesn't seem to affect mousing when set to no, but saves a few bytes when yes		# Not sure what this does
CUSTOM_POINTING_DEVICE  = yes		# This is a Drashna thing, for pointing.c/h

# Split settings
SPLIT_KEYBOARD 			= yes
CUSTOM_SPLIT_TRANSPORT_SYNC = yes

# Other settings
CUSTOM_UNICODE_ENABLE        = no # doesn't seem to impact size when set to no
USER_NAME 					:= christrotter

# Space-saving options - these save 4.5kb
LTO_SUPPORTED 			= yes
LTO_ENABLE 				= yes		# Does greater compression during build
SPACE_CADET_ENABLE 		= no
GRAVE_ESC_ENABLE 		= no
# ensuring other stuff is disabled for the same reason
RGBLIGHT_ENABLE              = no
AUDIO_ENABLE                 = no
HAPTIC_ENABLE                = no
OLED_ENABLE                  = no
WPM_ENABLE                   = no
ENCODER_ENABLE               = no
AUTOCORRECTION_ENABLE        = no
SWAP_HANDS_ENABLE            = no
CAPS_WORD_ENABLE             = no
AUTO_SHIFT_ENABLE			 = no