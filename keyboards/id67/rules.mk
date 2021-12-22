# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse key
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
AUDIO_ENABLE = no           # Audio output

RGB_MATRIX_ENABLE = yes     # Enable RGB Matrix feature
RGB_MATRIX_DRIVER = WS2812 	# ID67 uses WS2812 driver

KEY_LOCK_ENABLE = yes       # Enable KC_LOCK support

LAYOUTS = 65_ansi_blocker
