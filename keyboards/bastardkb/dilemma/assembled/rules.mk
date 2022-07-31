# MCU name
MCU = RP2040

# Bootloader selection
BOOTLOADER = rp2040

# RP2040-specific options
PICO_INTRINSICS_ENABLED = no # ATM Unsupported by ChibiOS.
SERIAL_DRIVER = vendor

# Assembled version uses SPI instead of I2C.
POINTING_DEVICE_DRIVER = cirque_pinnacle_spi
