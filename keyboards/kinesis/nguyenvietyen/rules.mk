# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
COMMAND_ENABLE = yes
NKRO_ENABLE = yes           # Enable N-Key Rollover
SLEEP_LED_ENABLE = yes
CUSTOM_MATRIX = lite
SRC += matrix.c

# experimentally determined to be sufficient :)
DEBOUNCE=1
