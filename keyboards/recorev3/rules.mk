# Debounce Configuration
SRC += asym_instant_defer_pk.c

# RGB Configuration
WS2812_DRIVER = vendor
RGBLIGHT_ENABLE = yes
RGBLIGHT_DRIVER = ws2812 

# Allow String Macros
SEND_STRING_ENABLE = yes
 
# Split Board Configuration
SERIAL_DRIVER = usart
SERIAL_DRIVER = vendor