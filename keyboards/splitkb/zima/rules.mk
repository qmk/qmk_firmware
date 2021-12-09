# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

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
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
AUDIO_ENABLE = yes         # Audio output

ENCODER_ENABLE = yes       # ENables the use of one or more encoders
OLED_ENABLE = yes
OLED_DRIVER = SSD1306      # Enables the use of OLED displays
HAPTIC_ENABLE = yes        # Supported but not included by defaut
HAPTIC_DRIVER = DRV2605L

LTO_ENABLE = yes
