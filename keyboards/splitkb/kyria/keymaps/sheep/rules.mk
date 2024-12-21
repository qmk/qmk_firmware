# Required
OLED_ENABLE = yes
OLED_DRIVER = SSD1306		# Enables the use of OLED displays
ENCODER_ENABLE = yes    	# Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes   	# Enable keyboard RGB underglow
#WPM_ENABLE = yes 			# Enables word per minute computation
DYNAMIC_MACRO_ENABLE = yes 	# Active les macros dynimaques 				[+450o]	
MOUSEKEY_ENABLE  = yes 		# Mouse keys(+4700)

# Size reduction
CONSOLE_ENABLE	 = no
COMMAND_ENABLE   = no 		# Commands for debug and configuration
UNICODE_ENABLE   = no		# Unicode
EXTRAFLAGS += -flto 		# Link Time Optimization
EXTRAFLAGS += -Wall
SRC += sheep.c