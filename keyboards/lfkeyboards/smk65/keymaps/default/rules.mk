# Build Options
#   change yes to no to disable
#
AUDIO_ENABLE = no              # Audio output
RGBLIGHT_ENABLE = no           # Enable keyboard RGB underglow

ISSI_ENABLE = no               # If the I2C pullup resistors aren't install this must be disabled
WATCHDOG_ENABLE = no           # Resets keyboard if matrix_scan isn't run every 250ms


ifeq ($(strip $(ISSI_ENABLE)), yes)
    TMK_COMMON_DEFS += -DISSI_ENABLE
endif

ifeq ($(strip $(WATCHDOG_ENABLE)), yes)
    TMK_COMMON_DEFS += -DWATCHDOG_ENABLE
endif
