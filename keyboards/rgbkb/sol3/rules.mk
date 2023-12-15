# Touch encoder needs
VPATH += keyboards/rgbkb/common
SRC += touch_encoder.c
SRC += common_oled.c
QUANTUM_LIB_SRC += i2c_master.c

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
AUDIO_DRIVER = dac_additive

DYNAMIC_MACRO_ENABLE = yes
DIP_SWITCH_ENABLE = yes

RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes

OLED_ENABLE = yes

ENCODER_ENABLE = yes

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart
LTO_ENABLE = yes
OPT = 3

OPT_DEFS += -DOLED_FONT_H=\"keyboards/rgbkb/common/glcdfont.c\"

DEFAULT_FOLDER = rgbkb/sol3/rev1
