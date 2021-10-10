# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
BOOTMAGIC_ENABLE = no     # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no      # Mouse keys
EXTRAKEY_ENABLE = no      # Audio control and System control
CONSOLE_ENABLE = no       # Console for debug
COMMAND_ENABLE = no       # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no     # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no          # USB Nkey Rollover
BACKLIGHT_ENABLE = no     # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow
AUDIO_ENABLE = no         # Audio output
RGB_MATRIX_ENABLE = no

AUDIO_SUPPORTED = no
RGB_MATRIX_SUPPORTED = yes
RGBLIGHT_SUPPORTED = yes

POINTING_DEVICE_ENABLE = yes
MOUSE_SHARED_EP = no

SPLIT_KEYBOARD = yes
LAYOUTS = split_3x5_3

SRC += drivers/sensors/pmw3360.c
QUANTUM_LIB_SRC += spi_master.c
