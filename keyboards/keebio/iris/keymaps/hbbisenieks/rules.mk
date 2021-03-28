RGBLIGHT_ENABLE = yes
BACKLIGHT_ENABLE = yes

# Comment out for pro-micro board
BOOTLOADER = atmel-dfu


ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
