BOOTMAGIC_ENABLE   = lite
TAP_DANCE_ENABLE   = no
COMMAND_ENABLE     = no  # Commands for debug and configuration
CONSOLE_ENABLE     = no
SPACE_CADET_ENABLE = no

ifeq ($(strip $(KEYBOARD)), ergodox_ez)
    RGBLIGHT_ENABLE            = yes
    RGB_MATRIX_ENABLE          = yes
    RGBLIGHT_TWINKLE           = no
    INDICATOR_LIGHTS           = no
    RGBLIGHT_STARTUP_ANIMATION = yes
    PIMORONI_TRACKBALL_ENABLE  = yes
    MOUSEKEY_ENABLE            = no
endif

UNICODE_ENABLE     = no
UNICDOEMAP_ENABLE  = no


DEBOUNCE_TYPE     = eager_pr
