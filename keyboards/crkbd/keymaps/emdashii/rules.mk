MOUSEKEY_ENABLE = yes    			# Mouse keys
RGBLIGHT_ENABLE = yes    			# Enable WS2812 RGB underlight. Might need to be no?
RGB_MATRIX_ENABLE = yes
OLED_ENABLE     = yes
OLED_DRIVER     = SSD1306
LTO_ENABLE      = yes
WPM_ENABLE 			= yes			# Enable word per minute counter
LTO_ENABLE 			= yes			# Makes hex file smaller
OLED_DRIVER_ENABLE = yes			# Enable OLEDs

SRC += ./oled.c ./rgb.c
