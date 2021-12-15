<<<<<<< HEAD
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
=======
BOOTMAGIC_ENABLE   = yes      # Enable Bootmagic Lite
>>>>>>> 3fa592a4024a24a636fa0c562e6761667a94f565
TAP_DANCE_ENABLE   = no
COMMAND_ENABLE     = no  # Commands for debug and configuration
CONSOLE_ENABLE     = no
SPACE_CADET_ENABLE = no

ifeq ($(strip $(KEYBOARD)), ergodox_ez)
    RGBLIGHT_ENABLE            = yes
    RGB_MATRIX_ENABLE          = yes
    INDICATOR_LIGHTS           = no
    RGBLIGHT_STARTUP_ANIMATION = yes
    PIMORONI_TRACKBALL_ENABLE  = no
    MOUSEKEY_ENABLE            = no
endif

UNICODE_ENABLE        = no
UNICDOEMAP_ENABLE     = no
CUSTOM_UNICODE_ENABLE = no

<<<<<<< HEAD

=======
>>>>>>> 3fa592a4024a24a636fa0c562e6761667a94f565
DEBOUNCE_TYPE     = sym_eager_pr
