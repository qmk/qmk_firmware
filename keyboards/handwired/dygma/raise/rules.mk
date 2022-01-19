# MCU name
MCU = STM32F411

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = no        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = custom
CUSTOM_MATRIX = lite

# TODO(ibash) we don't actually need to enable raw, but there's some side effect
# in the usb driver this triggers that allows mousekeys to work. The same side
# effect happens if console or midi is enabled -- so something to do with
# alternate usb endpoints.
RAW_ENABLE = yes

QUANTUM_LIB_SRC += i2c_master.c
SRC += leds.c matrix.c

DEFAULT_FOLDER = handwired/dygma/raise/ansi
