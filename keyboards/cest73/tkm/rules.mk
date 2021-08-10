# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = halfkay

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes  # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no    # Mouse keys
EXTRAKEY_ENABLE = yes   # Audio control and System control
CONSOLE_ENABLE = no     # Console for debug
COMMAND_ENABLE = no     # Commands for debug and configuration
SLEEP_LED_ENABLE = no   # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes       # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality
UNICODE_ENABLE = no     #
UNICODEMAP_ENABLE = no  # send Unicode characters using X(<map index>) in your keymap. All code points (up to 0x10FFFF) are supported
UCIS_ENABLE = no        # send Unicode characters by inputting a mnemonic. All possible code points (up to 0x10FFFF) are supported

AUDIO_ENABLE = no
RGBLIGHT_ENABLE = no
