# MCU name
MCU = RP2040

# Bootloader selection
BOOTLOADER = rp2040

PICO_INTRINSICS_ENABLED = no # ATM Unsupported by ChibiOS!
VIA_ENABLE = no
# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System controls
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = yes         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output

LAYOUTS = ortho_4x10

QUANTUM_PAINTER_ENABLE = yes
# QUANTUM_PAINTER_DEBUG = yes
QUANTUM_PAINTER_DRIVERS = st7789_spi
QUANTUM_PAINTER_SUPPORTS_256_PALETTE = yes
QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE = 1096

SRC += monke.qgf.c