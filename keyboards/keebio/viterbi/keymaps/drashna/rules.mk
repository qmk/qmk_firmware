BOOTMAGIC_ENABLE  = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE   = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE   = yes       # Audio control and System control(+450)
CONSOLE_ENABLE    = no         # Console for debug(+400)
COMMAND_ENABLE    = no        # Commands for debug and configuration
TAP_DANCE_ENABLE  = no
RGBLIGHT_ENABLE   = yes
AUDIO_ENABLE      = yes
NKRO_ENABLE       = yes
SPLIT_KEYBOARD    = no
SPACE_CADET_ENABLE = no

NO_SECRETS        = yes
MACROS_ENABLED    = yes
INDICATOR_LIGHTS  = no
RGBLIGHT_TWINKLE  = no
LAYOUTS = ortho_5x7

# SRC := $(filter-out serial.c matrix.c i2c.c split_util.c,$(SRC))
# SRC := $(filter-out serial.c,$(SRC))
# SRC := $(filter-out matrix.c,$(SRC))
# SRC := $(filter-out i2c.c,$(SRC))
# SRC := $(filter-out split_util.c,$(SRC))
# SRC += quantum/matrix.c

BOOTLOADER        = qmk-dfu
