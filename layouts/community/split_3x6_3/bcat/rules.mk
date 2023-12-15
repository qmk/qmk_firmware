BCAT_OLED_PET = luna

ifeq ($(strip $(KEYBOARD)), crkbd/rev1)
	BOOTLOADER = atmel-dfu  # Elite-C

	OLED_ENABLE = yes  # dual 128x32 OLED screens
	RGB_MATRIX_ENABLE = yes  # per-key RGB and underglow
endif
