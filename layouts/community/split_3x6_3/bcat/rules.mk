ifeq ($(strip $(KEYBOARD)), crkbd/rev1)
	BOOTLOADER = atmel-dfu  # Elite-C

	RGB_MATRIX_ENABLE = yes  # per-key RGB and underglow
endif
