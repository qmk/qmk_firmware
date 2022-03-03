# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = qmk-dfu

# Build Options
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
NKRO_ENABLE = yes           # Enable N-key Rollover
EXTRAKEY_ENABLE = yes       # Audio control and System control

LAYOUTS = ortho_4x12

RGBLIGHT_SUPPORTED = no
