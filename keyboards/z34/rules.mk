# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no           # USB Nkey Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no       # Enable keyboard RGB underglow
AUDIO_ENABLE = no          # Audio output
SPLIT_KEYBOARD = yes       # Split common
LTO_ENABLE = yes           # Enables Link Time Optimization (LTO) which reduces the compiled size

# There are no extra pins, so we make sure to disable OLED and Encoders
OLED_SUPPORTED = no        # Enables the use of OLED displays
ENCODER_SUPPORTED = no      # Enables the use of encoders

