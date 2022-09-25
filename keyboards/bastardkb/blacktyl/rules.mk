# MCU name
MCU = STM32F401
# or
# MCU = STM32F411
# For newer blackpills
BOOTMAGIC_ENABLE = yes 
LAYOUTS = split_3x5_3

# Bootloader selection
BOOTLOADER = stm32-dfu

# CONSOLE_ENABLE         = yes
DEBOUNCE_TYPE          = asym_eager_defer_pk
# EEPROM_DRIVER          = spi
# KEYBOARD_SHARED_EP     = yes
# POINTING_DEVICE_DRIVER = pmw3360
# POINTING_DEVICE_ENABLE = yes
# RGBLIGHT_DRIVER        = WS2812
# RGBLIGHT_ENABLE        = no
# SERIAL_DRIVER          = bitbang
SERIAL_DRIVER          = usart
SPLIT_KEYBOARD         = yes
# VIA_ENABLE             = no
# WS2812_DRIVER          = pwm
MOUSEKEY_ENABLE = yes 
EXTRAKEY_ENABLE = yes

CAPS_WORD_ENABLE = yes
