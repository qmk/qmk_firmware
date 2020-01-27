BOOTMAGIC_ENABLE  = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE   = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE   = yes       # Audio control and System control(+450)
CONSOLE_ENABLE    = no         # Console for debug(+400)
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
