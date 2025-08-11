# Processor frequency
F_CPU = 8000000

PS2_DRIVER = interrupt
CUSTOM_MATRIX = yes

WS2812_DRIVER_REQUIRED = yes
BATTERY_DRIVER_REQUIRED = yes

SRC += rgbsps.c
SRC += matrix.c
