# Enable additional features.

# Disabling MouseKey because it breaks my KVM switch
MOUSEKEY_ENABLE = no

# Ensure sym_defer_g is used.
# It seems sym_defer_pk results in significant chattering, even with an 8ms debounce time.
DEBOUNCE_TYPE = sym_defer_g

# Useful for debugging
# CONSOLE_ENABLE = yes
# DEBUG_MATRIX_SCAN_RATE_ENABLE = yes
# DEBUG_MATRIX_SCAN_RATE = yes

# Encoder Map support
ENCODER_MAP_ENABLE = yes

# Enables VIA
VIA_ENABLE = yes
