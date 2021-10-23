BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE   = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE   = yes       # Audio control and System control(+450)
CONSOLE_ENABLE    = no         # Console for debug(+400)
COMMAND_ENABLE    = no        # Commands for debug and configuration
TAP_DANCE_ENABLE  = no
NKRO_ENABLE       = yes

ifeq ($(strip $(KEYBOARD)), fractal)
    RGB_MATRIX_ENABLE           = no
    AUDIO_ENABLE                = yes
    AUDIO_SUPPORTED             = yes
    RGBLIGHT_SUPPORTED          = yes
    RGBLIGHT_ENABLE             = yes
    RGBLIGHT_STARTUP_ANIMATION  = yes
    BOOTLOADER                  = qmk-dfu
endif
