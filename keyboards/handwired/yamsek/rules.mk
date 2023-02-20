#
# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output

CC_FLAGS += -Werror


# override quantums matrix.c with custom matrix file
#   which uses a row-oriented internal data-structure, we use a column oriented
#   that was inherited from the I2C/MCP23018 code of the ergodox/ez
CUSTOM_MATRIX = yes
SRC += matrix.c

RGBLIGHT_ENABLE = no
RGBLIGHT_DRIVER = WS2812

VPATH += drivers/gpio
SRC += mcp23018.c
QUANTUM_LIB_SRC += i2c_master.c
OPT_DEFS += -DHAL_USE_I2C=TRUE

DEFAULT_FOLDER = yamsek/atmega32u4
