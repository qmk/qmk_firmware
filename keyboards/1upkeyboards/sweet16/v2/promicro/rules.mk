MCU = atmega32u4
BOOTLOADER = caterina
LINK_TIME_OPTIMIZATION_ENABLE=yes

## Features
BACKLIGHT_ENABLE = yes
LED_MATRIX_ENABLE = pinmatrix
CONSOLE_ENABLE = yes

## On a Pro Micro you have to choose between underglow and the rotary encoder.
RGBLIGHT_ENABLE = no
ENCODER_ENABLE = yes
