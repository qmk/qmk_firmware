# MCU name
MCU = STM32F401

# Address of the bootloader in system memory
STM32_BOOTLOADER_ADDRESS = 0x1FFF0000


CUSTOM_MATRIX = lite    # for using the A9 pin as matrix io

# # project specific file
QUANTUM_SRC += matrix.c


WS2812_DRIVER = pwm
