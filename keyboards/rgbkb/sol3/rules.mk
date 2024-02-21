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
AUDIO_DRIVER = dac_additive
OS_DETECTION_ENABLE = yes

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

DEFERRED_EXEC_ENABLE = yes
COMBO_ENABLE = yes
