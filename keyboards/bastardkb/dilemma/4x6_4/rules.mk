CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
MAGIC_ENABLE = yes			# Magic keycodes
TRI_LAYER_ENABLE = yes		# Tri Layers

AUDIO_SUPPORTED = no        # Audio is not supported
RGBLIGHT_SUPPORTED = no     # RGB underglow is supported, but not enabled by default

SERIAL_DRIVER = vendor

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_spi

# RP2040-specific options
PICO_INTRINSICS_ENABLED = no # ATM Unsupported by ChibiOS.
