SERIAL_DRIVER = vendor

POINTING_DEVICE_DRIVER = cirque_pinnacle_spi

QUANTUM_PAINTER_DRIVERS += st7789_spi
QUANTUM_PAINTER_LVGL_INTEGRATION = yes

SRC += lvgl_helpers.c \
	   display.c
