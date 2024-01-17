# Enable additional features.

# Disabling MouseKey because it breaks my KVM switch
MOUSEKEY_ENABLE = no

# Use sym_eager_pk for better latency when gaming.
#
# Previous issues with sym_defer_pk (and sym_eager_pk and debounce times
# shorter than 8ms) were due to Glorious' horrible hot-swap sockets. 
# These issues were 100% resolved after I replaced them with Gateron hot-swap sockets.
#
# The old sockets apparently didn't hold onto the legs of the switches at all.
#
# Using eager might not be a good idea with other switch types, but I only use 
# linears now, so this should be ok.
#
# asym_eager_defer_pk also works well and it is more resistant to chatter at
# the cost of delay when releasing a key being slightly higher.
DEBOUNCE_TYPE = sym_eager_pk

# Useful for debugging
# CONSOLE_ENABLE = yes
# DEBUG_MATRIX_SCAN_RATE_ENABLE = yes
# DEBUG_MATRIX_SCAN_RATE = yes

# Encoder Map support
ENCODER_MAP_ENABLE = yes

# Enables VIA
VIA_ENABLE = yes
