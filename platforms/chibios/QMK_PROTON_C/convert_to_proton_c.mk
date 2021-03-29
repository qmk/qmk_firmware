# Proton C MCU settings for converting AVR projects
TARGET := $(TARGET)_proton_c
MCU := STM32F303
BOARD := QMK_PROTON_C
OPT_DEFS += -DCONVERT_TO_PROTON_C

# These are defaults based on what has been implemented for ARM boards
AUDIO_ENABLE = yes
WS2812_DRIVER = bitbang

# Force task driven PWM until ARM can provide automatic configuration
BACKLIGHT_DRIVER = software