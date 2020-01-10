# MCU
MCU  = STM32F103
BOARD = pjf_keyboard
MCU_LDSCRIPT = pjf

# options
BOOTMAGIC_ENABLE = yes # Virtual DIP switch configuration
## (Note that for BOOTMAGIC on Teensy LC you have to use a custom .ld script.)
MOUSEKEY_ENABLE = no # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
CONSOLE_ENABLE = no# Console for debug
COMMAND_ENABLE = no # Commands for debug and configuration
NKRO_ENABLE = no # USB Nkey Rollover
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = yes

RGBLIGHT_CUSTOM_DRIVER = yes

SRC += drivers/arm/ws2812.c
