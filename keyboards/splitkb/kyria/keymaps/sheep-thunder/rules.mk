OLED_ENABLE = yes
OLED_DRIVER = SSD1306	# Enables the use of OLED displays
ENCODER_ENABLE = yes    # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes   # Enable keyboard RGB underglow
WPM_ENABLE = yes 		# Enables word per minute computation

# size reduction
CONSOLE_ENABLE	 = no
COMMAND_ENABLE   = no 	# Commands for debug and configuration
UNICODE_ENABLE   = no	# Unicode
MOUSEKEY_ENABLE  = no 	# Mouse keys(+4700)
EXTRAFLAGS += -flto 	# Link Time Optimization
SRC += sheep-thunder.c