# Touch encoder needs
VPATH += keyboards/rgbkb/common
SRC += touch_encoder.c
SRC += common_oled.c
QUANTUM_LIB_SRC += i2c_master.c

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
AUDIO_ENABLE = no           # Audio output

RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812

OLED_ENABLE = yes
OLED_DRIVER = SSD1306    # Enable the OLED Driver

ENCODER_ENABLE = yes

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart
LTO_ENABLE = yes
OPT = 3

OPT_DEFS += -DOLED_FONT_H=\"keyboards/rgbkb/common/glcdfont.c\"

DEFAULT_FOLDER = rgbkb/mun/rev1
