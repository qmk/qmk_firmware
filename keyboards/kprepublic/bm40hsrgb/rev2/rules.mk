# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes        # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes          # Mouse keys
EXTRAKEY_ENABLE = yes          # Audio control and System control
CONSOLE_ENABLE = no            # Console for debug
COMMAND_ENABLE = no            # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no          # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes           # Enable keyboard RGB underglow
MIDI_ENABLE = no               # MIDI support
AUDIO_ENABLE = no              # Audio output on port C6
RGB_MATRIX_ENABLE = yes        # Use RGB matrix
RGB_MATRIX_DRIVER = IS31FL3733
LAYOUTS = planck_mit

LTO_ENABLE = yes
