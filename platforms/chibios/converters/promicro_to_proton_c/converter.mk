# Proton C MCU settings for converting AVR projects
MCU := STM32F303
BOARD := QMK_PROTON_C
BOOTLOADER := stm32-dfu

# These are defaults based on what has been implemented for ARM boards
AUDIO_ENABLE ?= yes
WS2812_DRIVER ?= bitbang
