# Build Options
#   change yes to no to disable
#
AUDIO_ENABLE = yes              # Audio output on port C6
RGBLIGHT_ENABLE = yes         	# Disable RGB underlight
SLEEP_LED_ENABLE = yes          # Breathing sleep LED during USB suspend

ISSI_ENABLE = yes               # If the I2C pullup resistors aren't install this must be disabled
WATCHDOG_ENABLE = no            # Resets keyboard if matrix_scan isn't run every 250ms


ifeq ($(strip $(ISSI_ENABLE)), yes)
    TMK_COMMON_DEFS += -DISSI_ENABLE
endif

ifeq ($(strip $(WATCHDOG_ENABLE)), yes)
    TMK_COMMON_DEFS += -DWATCHDOG_ENABLE
endif
