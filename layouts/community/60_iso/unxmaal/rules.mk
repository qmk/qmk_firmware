# Only enable RGB on avr boards
ifndef MCU_FAMILY
    RGBLIGHT_ENABLE = yes          # Enable RGB Underglow
endif
