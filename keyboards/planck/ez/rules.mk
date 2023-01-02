# MCU name
MCU = STM32F303

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = yes          # Audio output
AUDIO_DRIVER = dac_additive
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.

ENCODER_ENABLE = yes
RGB_MATRIX_DRIVER = IS31FL3737

LAYOUTS = ortho_4x12 planck_mit
LAYOUTS_HAS_RGB = no

RGB_MATRIX_SUPPORTED = yes
RGBLIGHT_SUPPORTED = no
BAKCLIGHT_SUPPORTED = no

MOUSE_SHARED_EP = no

DEFAULT_FOLDER = planck/ez/base
