# MCU name
MCU = STM32F401
BOARD = BLACKPILL_STM32_F401
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
CAPS_WORD_ENABLE = yes
# POINTING_DEVICE_ENABLE = yes
# RGBLIGHT_DRIVER        = WS2812
# RGBLIGHT_ENABLE        = no
# SERIAL_DRIVER          = bitbang
SERIAL_DRIVER          = usart
SPLIT_KEYBOARD         = yes
# VIA_ENABLE             = no
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes

RGB_MATRIX_SUPPORTED = yes  # RGB matrix is supported and enabled by default
RGBLIGHT_SUPPORTED = no    # RGB underglow is supported, but not enabled by default
RGB_MATRIX_ENABLE = yes     # Enable keyboard RGB matrix functionality
RGB_MATRIX_DRIVER = ws2812

SPLIT_KEYBOARD = yes

MOUSE_SHARED_EP = no # Unify multiple HID interfaces into a single Endpoint
KEYBOARD_SHARED_EP = yes

