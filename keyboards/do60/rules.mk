# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
AUDIO_ENABLE = no           # Audio output
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
COMMAND_ENABLE = no         # Commands for debug and configuration
CONSOLE_ENABLE = no         # Console for debug
EXTRAKEY_ENABLE = yes       # Audio control and System control
MOUSEKEY_ENABLE = yes       # Mouse keys
NKRO_ENABLE = yes           # Enable N-Key Rollover
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight. 

LAYOUTS = 60_ansi 60_hhkb 60_ansi_split_bs_rshift
