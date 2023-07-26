# MCU
MCU = cortex-m0
ARMV = 6
USE_FPU = no
MCU_FAMILY = LPC
MCU_SERIES = LPC11Uxx
MCU_LDSCRIPT = LPC11U37F
MCU_STARTUP = lpc11uxx
BOARD = k70_vengeance_rgb

DEFAULT_FOLDER=corsair/k70_vengeance_rgb

#OPT_DEFS = -Wno-unused-function -fdump-rtl-dfinish -fstack-usage

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
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
LTO_ENABLE = yes			# Enables Link Time Optimization
# Bootloader selection
BOOTLOADER = custom
