CUSTOM_MATRIX = lite

CIE1931_CURVE = yes

QUANTUM_PAINTER_DRIVERS = ili9341_spi

SRC += \
	djinn_portscan_matrix.c \
	djinn_split_sync.c \
	djinn_usbpd.c

DEFAULT_FOLDER = tzarc/djinn/rev2
