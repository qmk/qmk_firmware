# MCU name
MCU = WB32FQ95

# Bootloader selection
BOOTLOADER = wb32-dfu

# Build Options
#   change yes to no to disable
#
KEYBOARD_SHARED_EP = no
BOOTMAGIC_ENABLE = no          # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes          # Mouse keys
EXTRAKEY_ENABLE = yes          # Audio control and System control
NKRO_ENABLE = yes              # Enable N-Key Rollover
CONSOLE_ENABLE = no            # Console for debug
COMMAND_ENABLE = no            # Commands for debug and configuration
BACKLIGHT_ENABLE = no          # Enable keyboard backlight functionality
AUDIO_ENABLE = no              # Audio output
ENCODER_ENABLE = yes           # Encoder
RGBLIGHT_ENABLE =  no          # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = yes        # RGB matrix
HAPTIC_ENABLE = no             # Haptic

EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = spi_flash

RGB_MATRIX_DRIVER = WS2812
