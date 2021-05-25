BOARD = PJRC_TEENSY_3_6
MCU   = MK66F18

# Debounce eagerly (report change immediately), keep per-key timers. We can use
# this because the kinT does not have to deal with noise.
DEBOUNCE_TYPE = sym_eager_pk
