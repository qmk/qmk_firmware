# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes           # USB Nkey Rollover

ARISTIDES_COMMON_FILES=../../../unicomp/classic_ultracl_post_2013/aristides_2862
SRC += $(ARISTIDES_COMMON_FILES)/matrix.c $(ARISTIDES_COMMON_FILES)/aristides_2862.c

CUSTOM_MATRIX = lite
DEBOUNCE_TYPE = sym_eager_pk
