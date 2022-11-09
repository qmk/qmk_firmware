# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no       	# Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = yes			# Enable RGB Matrix functionality.
RGB_MATRIX_DRIVER = WS2812	# RGB matrix driver.
AUDIO_ENABLE = yes          # Audio output
ENCODER_ENABLE = yes		    # Encoder functionality
