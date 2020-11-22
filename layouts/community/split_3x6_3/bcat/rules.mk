ifeq ($(strip $(KEYBOARD)), crkbd/rev1/common)
	BOOTLOADER = atmel-dfu  # Elite-C

	# Enable underglow only. (Split Common doesn't support RGB matrix on slave.)
	RGBLIGHT_ENABLE = yes
else ifeq ($(strip $(KEYBOARD)), crkbd/rev1/legacy)
	BOOTLOADER = atmel-dfu  # Elite-C

	RGB_MATRIX_ENABLE = WS2812  # per-key RGB and underglow
endif
