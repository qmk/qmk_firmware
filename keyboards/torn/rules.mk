# MCU name
MCU = atmega328p

# Bootloader selection
BOOTLOADER = USBasp

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = no        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
ENCODER_ENABLE = yes        # Enable rotary encoder
OLED_DRIVER_ENABLE = yes
CUSTOM_MATRIX = lite

SRC += matrix.c \
    mcp23018.c \
    torn_encoder.c \
    torn_oled.c
QUANTUM_LIB_SRC += i2c_master.c
