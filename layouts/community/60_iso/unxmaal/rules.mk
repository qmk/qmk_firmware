# Only enable RGBLIGHT on avr boards
ifeq ($(strip $(PLATFORM_KEY)),avr)
    # ...that are at least prepared for it
    ifdef RGBLIGHT_DRIVER
        RGBLIGHT_ENABLE = yes          # Enable RGB Underglow
    endif
endif
