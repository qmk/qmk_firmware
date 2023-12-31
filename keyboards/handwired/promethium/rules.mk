# Processor frequency
F_CPU = 8000000

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

WS2812_DRIVER_REQUIRED = yes
ANALOG_DRIVER_REQUIRED = yes

SRC += rgbsps.c
SRC += matrix.c

LTO_ENABLE = yes
