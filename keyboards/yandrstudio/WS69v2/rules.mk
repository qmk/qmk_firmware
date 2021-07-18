# MCU name
MCU = STM32F103

# Bootloader selection
BOOTLOADER = stm32duino

# change yes to no to disable
EXTRAKEY_ENABLE = yes        # Audio control and System control
NKRO_ENABLE = yes            # USB Nkey Rollover

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
WS2812_DRIVER = spi

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE