# MCU name
MCU = STM32F103

# Bootloader selection
BOOTLOADER = custom

MCU_LDSCRIPT = adelais_f103

BOARD = adelais_f103


RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = IS31FL3741
RGBLIGHT_ENABLE = yes
ENCODER_ENABLE = yes
WS2812_DRIVER = spi

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE