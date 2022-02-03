# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no  # Virtual DIP switch configuration
MOUSEKEY_ENABLE  = no  # Mouse keys
EXTRAKEY_ENABLE  = no  # Audio control and System control
CONSOLE_ENABLE   = yes # Console for debug
COMMAND_ENABLE   = yes # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE      = no  # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no # Enable keyboard backlight functionality
AUDIO_ENABLE     = no
RGBLIGHT_ENABLE  = no
OLED_DRIVER_ENABLE = no
