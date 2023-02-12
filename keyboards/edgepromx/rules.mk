# MCU name
MCU = MIMXRT1064

# Bootloader selection
BOOTLOADER = custom

# Build Options
#   change yes to no to disable
#
MCU_FAMILY = MIMXRT1064
MCU_SERIES = MIMXRT1064
MCU_LDSCRIPT = MIMXRT1064
MCU_STARTUP = MIMXRT1064
BOARD = EDGEPRO1
MCU = cortex-m4
ARMV = 7

BOOTMAGIC_ENABLE = no      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
UNICODE_ENABLE = yes
CUSTOM_MATRIX = lite
NO_USB_STARTUP_CHECK = yes

SRC += matrix.c
QUANTUM_LIB_SRC += i2c_master.c

LAYOUTS = ortho_4x12
