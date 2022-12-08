# MCU name
MCU = MK66FX1M0

# Debounce eagerly (report change immediately), keep per-key timers. We can use
# this because the kinT does not have to deal with noise.
DEBOUNCE_TYPE = sym_eager_pk
