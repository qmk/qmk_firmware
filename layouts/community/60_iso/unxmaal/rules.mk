# Only enable RGB on avr boards
ifeq ($(strip $(PLATFORM)), AVR)
    RGBLIGHT_ENABLE = yes          # Enable RGB Underglow
endif
