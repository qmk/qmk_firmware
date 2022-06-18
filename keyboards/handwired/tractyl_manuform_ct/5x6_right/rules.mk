# Hardware/build options
#DEFAULT_FOLDER 			= handwired/tractyl_manuform_ct/5x6_right
MCU 					= atmega32u4	# MCU name
BOOTLOADER 				= atmel-dfu		# Bootloader selection

# Functionality options
CONSOLE_ENABLE			= no        # Debugging things
MOUSEKEY_ENABLE 		= yes       # Mouse keys
EXTRAKEY_ENABLE 		= yes #commenting out to save space, troubleshooting       # Audio control and System control
NKRO_ENABLE 			= no # saves 300 bytes when no, trying to keep it off       # Enable N-Key Rollover
TAP_DANCE_ENABLE        = no		# temp disabling for troubleshooting

# Space-saving options
LTO_SUPPORTED 			= yes
LTO_ENABLE 				= yes		# Does greater compression during build
SPACE_CADET_ENABLE 		= no
GRAVE_ESC_ENABLE 		= no

# LED config
RGB_MATRIX_ENABLE 		= yes # this to 'no' didn't turn off the custom colours; rgb_matrix:yes/custom_rgb:no = no custom colours
CUSTOM_RGB_MATRIX       = yes # this to 'no' turned everything off
RGB_MATRIX_DRIVER 		= WS2812
# RGB_MATRIX_SOLID_COLOR 	= 1 

# Trackball settings
POINTING_DEVICE_ENABLE 	= yes
POINTING_DEVICE_DRIVER 	= pmw3360
MOUSE_SHARED_EP 		= yes # doesn't seem to affect mousing when set to no, but saves a few bytes when yes		# Not sure what this does
CUSTOM_POINTING_DEVICE  = yes		# This is a Drashna thing, for pointing.c/h

# Split settings
SPLIT_KEYBOARD 			= yes
# this also did not help resolve the "rgb missing from right side" issue
# but it seems like a good thing to have on...
CUSTOM_SPLIT_TRANSPORT_SYNC = yes

# Other settings
CUSTOM_UNICODE_ENABLE        = no # doesn't seem to impact size when set to no
USER_NAME 					:= christrotter

# ensuring other stuff is disabled
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