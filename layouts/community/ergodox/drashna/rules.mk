BOOTMAGIC_ENABLE   = yes      # Enable Bootmagic Lite
TAP_DANCE_ENABLE   = no
COMMAND_ENABLE     = no  # Commands for debug and configuration
CONSOLE_ENABLE     = no

ifeq ($(strip $(KEYBOARD)), ergodox_ez)
    RGBLIGHT_ENABLE            = yes
    RGB_MATRIX_ENABLE          = yes
    INDICATOR_LIGHTS           = no
    RGBLIGHT_STARTUP_ANIMATION = yes
endif

UNICODE_ENABLE        = no
UNICDOEMAP_ENABLE     = no
CUSTOM_UNICODE_ENABLE = no

ifeq ($(strip $(KEYBOARD)), hotdox76v2)
    OLED_ENABLE = no
    RGB_MATRIX_ENABLE = no
endif
