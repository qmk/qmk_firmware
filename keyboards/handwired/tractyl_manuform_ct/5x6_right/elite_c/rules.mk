# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# options
CONSOLE_ENABLE			= no
MOUSEKEY_ENABLE 		= yes       # Mouse keys
EXTRAKEY_ENABLE 		= yes       # Audio control and System control
NKRO_ENABLE 			= yes          # Enable N-Key Rollover
#TAP_DANCE_ENABLE        = yes

# space saving options
LTO_SUPPORTED 			= yes
LTO_ENABLE 				= yes
SPACE_CADET_ENABLE 		= no
GRAVE_ESC_ENABLE 		= no

# LED config
RGB_MATRIX_ENABLE 		= no
RGB_MATRIX_DRIVER 		= WS2812
RGB_MATRIX_SOLID_COLOR 	= 1 

# Trackball settings
POINTING_DEVICE_ENABLE 	= yes
POINTING_DEVICE_DRIVER 	= pmw3360
MOUSE_SHARED_EP 		= yes

# Split settings
SPLIT_KEYBOARD 			= yes
