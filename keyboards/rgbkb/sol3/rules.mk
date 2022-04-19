# MCU name
MCU = STM32F303

# Bootloader selection
BOOTLOADER = stm32-dfu

# Touch encoder needs
VPATH += keyboards/rgbkb/common
SRC += touch_encoder.c
SRC += common_oled.c
QUANTUM_LIB_SRC += i2c_master.c

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
AUDIO_ENABLE = yes          # Audio output
AUDIO_DRIVER = dac_additive

DYNAMIC_MACRO_ENABLE = yes
DIP_SWITCH_ENABLE = yes

WS2812_DRIVER = pwm
RGBLIGHT_ENABLE = no
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

# TODO: Implement fast matrix scanning
# matrix optimisations
# SRC += matrix.c

DEFAULT_FOLDER = rgbkb/sol3/rev1
