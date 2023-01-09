# Enable additional features.

# Disabling MouseKey because it breaks my KVM switch
MOUSEKEY_ENABLE = no

# Cherry MX-style switches and diodes are not susceptible to noise, no need for noise-resistant algorithms.
# This significantly reduces latency.
#
# The matrix scan frequency seems to be around 1820 Hz, so even sym_defer_g would perform ok,
# but the "defer" part would mean we would wait DEBOUNCE ms before sending any events.
# Using "asym_eager_defer_pk" does not seem to benefit us in anything.
# The GMMK Pro has more then enough system resources for a per-key algorithm.
# Using an "eager" algorithm leads to extremely low latency while also reducing the chances of chattering
# due to it's "post-event" debouncing (of sorts).
#
# I have observed zero chattering or double-keypress issues on my Gateron Yellow switches.
# Most chattering issues on the GMMK Pro seem to be related to its proprietary hot-swap sockets anyway.
DEBOUNCE_TYPE = sym_eager_pk

# Useful for debugging
# CONSOLE_ENABLE = yes
# DEBUG_MATRIX_SCAN_RATE_ENABLE = yes
# DEBUG_MATRIX_SCAN_RATE = yes
