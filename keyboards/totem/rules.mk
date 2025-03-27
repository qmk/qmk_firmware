# MCU name
MCU = RP2040

# Bootloader selection
BOOTLOADER = rp2040

# Ignore some warnings during the build, likely to be fixed before RP2040 PR is merged
ALLOW_WARNINGS = yes

# LTO must be disabled for RP2040 builds
LTO_ENABLE = no

SPLIT_KEYBOARD = yes
SWAP_HANDS_ENABLE = yes

# PIO serial/WS2812 drivers must be used on RP2040
SERIAL_DRIVER = vendor
WS2812_DRIVER = vendor

