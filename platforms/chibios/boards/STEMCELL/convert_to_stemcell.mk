# Proton C MCU settings for converting AVR projects
TARGET := $(TARGET)_stemcell
MCU := STM32F401
BOARD := STEMCELL
BOOTLOADER := tinyuf2
OPT_DEFS += -DCONVERT_TO_STEMCELL

SERIAL_DRIVER := usart

# These are defaults based on what has been implemented for ARM boards
AUDIO_ENABLE ?= no
WS2812_DRIVER ?= bitbang
