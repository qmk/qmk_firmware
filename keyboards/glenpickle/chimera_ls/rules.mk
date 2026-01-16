CUSTOM_MATRIX = lite

# project specific files
SRC += matrix.c
UART_DRIVER_REQUIRED = yes

# Disable unsupported hardware
RGBLIGHT_SUPPORTED = no
AUDIO_SUPPORTED = no
BACKLIGHT_SUPPORTED = no
