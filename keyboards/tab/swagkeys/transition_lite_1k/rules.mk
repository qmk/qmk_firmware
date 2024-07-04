
MCU_LDSCRIPT = STM32F103xB_uf2boot
BOARD        = STM32_F103_STM32DUINO
BOOTLOADER   = uf2boot

SRC += transition_lite_1k_impl.c ws2812_custom.c
