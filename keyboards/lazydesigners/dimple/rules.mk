# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes        # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
NKRO_ENABLE = yes            # USB Nkey Rollover
BACKLIGHT_ENABLE = no        # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow

# Disable unsupported hardware
AUDIO_SUPPORTED = no
BACKLIGHT_SUPPORTED = no
