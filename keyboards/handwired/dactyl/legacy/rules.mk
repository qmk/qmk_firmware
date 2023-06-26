# Build Options
#   change yes to no to disable
#
CUSTOM_MATRIX = yes     # Custom matrix file for the Dactyl
UNICODE_ENABLE = yes    # Unicode
SWAP_HANDS_ENABLE = yes # Allow swapping hands of keyboard

# project specific files
QUANTUM_LIB_SRC += i2c_master.c
SRC += matrix.c
