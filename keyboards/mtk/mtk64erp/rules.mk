# MCU name
MCU = RP2040

# Bootloader selection
BOOTLOADER = rp2040

RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
WS2812_DRIVER = vendor
AUDIO_ENABLE = no           # Audio output
LTO_ENABLE = yes

#  Trackball.
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3389
SERIAL_DRIVER = vendor
SPI_DRIVER_REQUIRED = yes
USE_DEVICE_pmw3389 = yes
