# MCU name
MCU = STM32F303
BOARD = QMK_PROTON_C

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
CONSOLE_ENABLE = no  # Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
NKRO_ENABLE = yes     # USB Nkey Rollover
AUDIO_ENABLE = yes   # Doot
RGBLIGHT_ENABLE = no
TAP_DANCE_ENABLE = no
UNICODE_ENABLE = no
UNICODEMAP_ENABLE = yes
