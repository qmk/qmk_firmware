MCU_FAMILY = MIMXRT1062
MCU_SERIES = MIMXRT1062
MCU_LDSCRIPT = MIMXRT1062
MCU_STARTUP = MIMXRT1062
BOARD = IC_TEENSY_4_1
MCU = cortex-m4
ARMV = 7

# Debounce eagerly (report change immediately), keep per-key timers. We can use
# this because the Cherry MX keyswitches on the Kinesis only produce noise while
# pressed.
DEBOUNCE_TYPE = sym_eager_pk

FIRMWARE_FORMAT = hex
