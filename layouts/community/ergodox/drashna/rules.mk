BOOTMAGIC_ENABLE   = lite
TAP_DANCE_ENABLE   = yes
COMMAND_ENABLE     = no  # Commands for debug and configuration
CONSOLE_ENABLE     =
SPACE_CADET_ENABLE = no

ifeq ($(strip $(KEYBOARD)), ergodox_ez)
    RGBLIGHT_ENABLE    = yes
    RGB_MATRIX_ENABLE  = yes
    RGBLIGHT_TWINKLE   = no
    INDICATOR_LIGHTS   = no
    RGBLIGHT_STARTUP_ANIMATION = yes
endif

UNICODE_ENABLE     = yes
UNICDOEMAP_ENABLE  = no


DEBOUNCE_TYPE     = eager_pr
