# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
AUDIO_ENABLE = no           # Audio output
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
COMMAND_ENABLE = no         # Commands for debug and configuration
CONSOLE_ENABLE = no         # Console for debug
EXTRAKEY_ENABLE = yes       # Audio control and System control
MOUSEKEY_ENABLE = yes       # Mouse keys
NKRO_ENABLE = yes           # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight. 

LAYOUTS = 60_ansi
