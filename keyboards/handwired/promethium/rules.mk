# MCU name
MCU = atmega32u4

# Processor frequency
F_CPU = 8000000

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
PS2_MOUSE_ENABLE = yes
PS2_ENABLE = yes
PS2_DRIVER = interrupt
CUSTOM_MATRIX = yes
BLUETOOTH_ENABLE = yes
BLUETOOTH_DRIVER = BluefruitLE

SRC += ws2812.c
SRC += rgbsps.c
SRC += analog.c
SRC += matrix.c

LTO_ENABLE = yes
