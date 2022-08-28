# MCU name
MCU = STM32F401
# or
# MCU = STM32F411
# For newer blackpills
BOOTMAGIC_ENABLE = yes 
LAYOUTS = split_3x5_3

# Bootloader selection
BOOTLOADER = stm32-dfu

CONSOLE_ENABLE         = yes
DEBOUNCE_TYPE          = asym_eager_defer_pk
# EEPROM_DRIVER          = spi
# KEYBOARD_SHARED_EP     = yes
# POINTING_DEVICE_DRIVER = pmw3360
# POINTING_DEVICE_ENABLE = yes
RGBLIGHT_SUPPORTED = yes    # RGB underglow is supported, but not enabled by default
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
RGBLIGHT_DRIVER        = WS2812
RGB_MATRIX_SUPPORTED = yes  # RGB matrix is supported and enabled by default
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGB_MATRIX_ENABLE = yes     # Enable keyboard RGB matrix functionality
RGB_MATRIX_DRIVER = WS2812  # RGB matrix driver support
WS2812_DRIVER = pwm
# SERIAL_DRIVER          = bitbang
SERIAL_DRIVER          = usart
SPLIT_KEYBOARD         = yes
# VIA_ENABLE             = no
MOUSEKEY_ENABLE = yes 
EXTRAKEY_ENABLE = yes


