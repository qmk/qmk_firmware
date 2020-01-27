BOOTMAGIC_ENABLE  = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE   = no       # Mouse keys
EXTRAKEY_ENABLE   = yes       # Audio control and System control
CONSOLE_ENABLE    = no         # Console for debug
COMMAND_ENABLE    = no        # Commands for debug and configuration
TAP_DANCE_ENABLE  = no
NKRO_ENABLE       = yes

ifeq ($(strip $(KEYBOARD)), fractal)
    RGB_MATRIX_ENABLE   = no
    AUDIO_ENABLE        = yes
    RGBLIGHT_ENABLE     = yes
    RGBLIGHT_TWINKLE    = yes
    BOOTLOADER          = qmk-dfu
endif
