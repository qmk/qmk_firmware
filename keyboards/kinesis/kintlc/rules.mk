# MCU name
MCU = MKL26Z64
# This MCU is not in the main CHIBIOS repo but in the CHIBIOS_CONTRIB repo.
USE_CHIBIOS_CONTRIB = yes

# Debounce eagerly (report change immediately), keep per-key timers. We can use
# this because the Cherry MX keyswitches on the Kinesis only produce noise while
# pressed.
DEBOUNCE_TYPE = sym_eager_pk
