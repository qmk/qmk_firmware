# Touch encoder needs
VPATH += keyboards/rgbkb/common
SRC += touch_encoder.c
SRC += common_oled.c
I2C_DRIVER_REQUIRED = yes

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
AUDIO_ENABLE = yes          # Audio output

DYNAMIC_MACRO_ENABLE = yes
DIP_SWITCH_ENABLE = yes

RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes

OLED_ENABLE = yes

ENCODER_ENABLE = yes

SERIAL_DRIVER = usart
LTO_ENABLE = yes
OPT = 3

DEFAULT_FOLDER = rgbkb/sol3/rev1
