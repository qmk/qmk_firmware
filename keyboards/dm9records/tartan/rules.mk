# MCU name
MCU = atmega328p

# Bootloader selection
BOOTLOADER = usbasploader

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output

LAYOUTS = 60_ansi 60_ansi_split_bs_rshift 60_iso 60_iso_split_bs_rshift
LAYOUTS_HAS_RGB = no

# Disable unsupported hardware
RGBLIGHT_SUPPORTED = no
AUDIO_SUPPORTED = no
BACKLIGHT_SUPPORTED = no
