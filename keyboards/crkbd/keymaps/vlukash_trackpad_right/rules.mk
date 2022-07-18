# Build Options
POINTING_DEVICE_ENABLE = yes # Generic Pointer, not as big as mouse keys hopefully.
POINTING_DEVICE_DRIVER = custom
MOUSEKEY_ENABLE = yes        # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes        # Audio control and System control(+450)
RGBLIGHT_ENABLE = yes        # Enable WS2812 RGB underlight.

BOOTLOADER = atmel-dfu

# Add support for the BB 8520 trackpad
SRC += trackpad.c
