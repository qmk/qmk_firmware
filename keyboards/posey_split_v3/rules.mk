# Debounce Configuration
# DEBOUNCE_TYPE = custom # asym, instant, then defer
SRC += debounce.c

# RGB Configuration
WS2812_DRIVER = vendor
RGBLIGHT_ENABLE = yes
RGBLIGHT_DRIVER = WS2812 

# Allow String Macros
SEND_STRING_ENABLE = yes
 
# Split Board Configuration
SERIAL_DRIVER = usart
SERIAL_DRIVER = vendor