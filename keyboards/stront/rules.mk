# choose pointing device driver:
POINTING_DEVICE_DRIVER = cirque_pinnacle_spi
# POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
# POINTING_DEVICE_DRIVER = azoteq_iqs5xx

QUANTUM_PAINTER_LVGL_INTEGRATION = yes
# choose one display driver:
QUANTUM_PAINTER_DRIVERS = st7789_spi # rectangular display
# QUANTUM_PAINTER_DRIVERS = gc9a01_spi # round display

SRC += lvgl_helpers.c \
	   display.c

DEFAULT_FOLDER = stront/38keys
