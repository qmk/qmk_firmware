# MCU name
MCU = atmega32u4

# Processor frequency
F_CPU = 8000000

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
LTO_ENABLE = yes
BOOTMAGIC_ENABLE = yes     # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes      # Mouse keys [NOTE TO SELF CHANGE TO YES]
EXTRAKEY_ENABLE = yes      # Audio control and System control [NOTE TO SELF CHANGE TO YES]
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes          # Enable N-Key Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
ENCODER_ENABLE = yes	   # Enable encoder
MIDI_ENABLE = yes          # Enable MIDI