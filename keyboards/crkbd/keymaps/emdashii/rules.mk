MOUSEKEY_ENABLE = yes    			# Mouse keys
RGBLIGHT_ENABLE = no    			# Enable WS2812 RGB underlight. Might need to be no?
RGB_MATRIX_ENABLE = yes
OLED_ENABLE     = yes
OLED_DRIVER     = SSD1306
WPM_ENABLE 			= no			# Enable word per minute counter
LTO_ENABLE 			= yes			# Makes hex file smaller
#OLED_DRIVER_ENABLE = yes			# Enable OLEDs

SRC += ./oled.c ./rgb.c
