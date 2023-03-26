# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes           # USB Nkey Rollover

SRC += matrix.c
CUSTOM_MATRIX = lite
DEBOUNCE_TYPE = sym_eager_pk

HAPTIC_ENABLE = yes
HAPTIC_DRIVER = SOLENOID

VPATH += lib/pico-sdk/src/rp2_common/hardware_spi/include
SRC += lib/pico-sdk/src/rp2_common/hardware_spi/spi.c
