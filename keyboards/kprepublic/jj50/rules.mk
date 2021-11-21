# MCU name
MCU = atmega32a

# Bootloader selection
BOOTLOADER = bootloadhid

# build options
BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no    # Mouse keys
EXTRAKEY_ENABLE = yes   # Audio control and System control
CONSOLE_ENABLE = no     # Console for debug
COMMAND_ENABLE = no     # Commands for debug and configuration
NKRO_ENABLE = no        # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes   # Enable keyboard underlight functionality
WS2812_DRIVER = i2c     # This driver powers the RGB Lighting and RGB Matrix features
SLEEP_LED_ENABLE = no   # Breathing sleep LED during USB suspend - # Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
LTO_ENABLE = yes        # Enable link time optimization

LAYOUTS = ortho_5x12
