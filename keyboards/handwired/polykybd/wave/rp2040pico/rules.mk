# MCU name
MCU = RP2040

# Bootloader selection
BOOTLOADER = rp2040

# Build Options
WS2812_DRIVER = vendor

# RP2040-specific options
ALLOW_WARNINGS = yes
PICO_INTRINSICS_ENABLED = no # ATM Unsupported by ChibiOS.

ENCODER_ENABLE = no

#POINTING_DEVICE_ENABLE = yes

