# MCU name
MCU = STM32F303

# Touch encoder needs
SRC += ../common/touch_encoder.c
SRC += ../common/common_oled.c
QUANTUM_LIB_SRC += i2c_master.c

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
## (Note that for BOOTMAGIC on Teensy LC you have to use a custom .ld script.)
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
AUDIO_ENABLE = no           # Audio output
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID

WS2812_DRIVER = pwm
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend

OLED_ENABLE = yes
OLED_DRIVER = SSD1306    # Enable the OLED Driver

ENCODER_ENABLE = yes

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart
LTO_ENABLE = yes
OPT = 3

OPT_DEFS += -DOLED_FONT_H=\"../common/glcdfont.c\"
OPT_DEFS += -Ikeyboards/rgbkb/common

# matrix optimisations
SRC += matrix.c

DEFAULT_FOLDER = rgbkb/mun/rev1
