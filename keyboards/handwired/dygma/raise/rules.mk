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

# TODO(ibash) we don't actually need to enable raw, but there's some side effect
# in the usb driver this triggers that allows mousekeys to work. The same side
# effect happens if console or midi is enabled -- so something to do with
# alternate usb endpoints.
RAW_ENABLE = yes
MOUSEKEY_ENABLE = yes

QUANTUM_LIB_SRC += i2c_master.c
SRC += leds.c
SRC += matrix.c
