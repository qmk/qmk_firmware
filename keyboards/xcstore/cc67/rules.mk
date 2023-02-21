SRC += matrix.c

# Custom matrix
CUSTOM_MATRIX = lite

# RGB Matrix enabled
WS2812_DRIVER = pwm

# Wear-levelling driver
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = legacy

LAYOUTS = 65_ansi_blocker
