# MCU name
MCU = STM32F072

# Bootloader selection
BOOTLOADER = stm32-dfu

DFU_SUFFIX_ARGS = -v FFFF -p FFFF

# Build Options
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # USB Nkey Rollover
AUDIO_ENABLE = no           # Audio output


BACKLIGHT_ENABLE = no	# Enable keyboard backlight(per switch) functionality
RGB_MATRIX_ENABLE = no	# This is for per switch RGB which we are not using

RGBLIGHT_ENABLE = yes	# Enable WS2812 RGB underglow.