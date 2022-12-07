# MCU name
MCU = STM32L422

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output

EEPROM_DRIVER = i2c

RGBLIGHT_ENABLE = yes
WS2812_DRIVER = bitbang

LTO_ENABLE = yes
OPT = 2

# LAYOUTS = LAYOUT_60_ansi_tsangan_split_rshift
