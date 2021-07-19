# MCU name
MCU = STM32F411

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
BOOTMAGIC_ENABLE = no
NKRO_ENABLE = no # USB Nkey Rollover
CUSTOM_MATRIX = yes

# CONSOLE_ENABLE = yes

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = custom

QUANTUM_LIB_SRC += i2c_master.c
SRC += leds.c
SRC += matrix.c
