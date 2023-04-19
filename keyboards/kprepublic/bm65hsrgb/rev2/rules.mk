# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
LTO_ENABLE = yes

LAYOUTS = 65_ansi_blocker

# RGB Matrix is required to support per-key LEDs connected to IS31FL3741.
RGB_MATRIX_ENABLE = yes
RGBLIGHT_SUPPORTED = no

# The custom RGB Matrix driver combines IS31FL3741 and WS2812; things that are
# normally done by common_features.mk for both of these drivers need to be done
# here manually.
RGB_MATRIX_DRIVER = custom
COMMON_VPATH += $(DRIVER_PATH)/led/issi
SRC += is31fl3741.c
QUANTUM_LIB_SRC += i2c_master.c
WS2812_DRIVER_REQUIRED = yes

