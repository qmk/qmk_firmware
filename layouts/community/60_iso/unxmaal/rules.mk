# Only enable RGBLIGHT on avr boards
ifeq ($(strip $(PLATFORM_KEY)),avr)
    # ...that are at least prepared for it
    ifeq ($(strip $(RGBLIGHT_SUPPORTED)),yes)
        RGBLIGHT_ENABLE = yes          # Enable RGB Underglow
    endif
endif
