# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
MIDI_ENABLE = yes           # MIDI support
ENCODER_ENABLE = yes        # encoder on mute button
SPLIT_KEYBOARD = yes        # Enables split keyboard support
# RGB_MATRIX_ENABLE is not suitable for giabalanai keyboard on the right side (there are dulpicate keys).
RGB_MATRIX_ENABLE = no      # Use RGB matrix (Don't enable this when RGBLIGHT_ENABLE is used.)
RGB_MATRIX_DRIVER = WS2812  # 2021/01/23 added.

LTO_ENABLE = yes
