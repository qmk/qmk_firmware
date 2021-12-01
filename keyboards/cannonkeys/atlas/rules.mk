# MCU name
MCU = STM32F072

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   comment out to disable the options.
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # USB Nkey Rollover
CUSTOM_MATRIX = no          # Custom matrix file
BACKLIGHT_ENABLE = no
RGBLIGHT_ENABLE = yes
WS2812_DRIVER = spi
