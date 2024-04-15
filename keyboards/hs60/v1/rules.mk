# Do not put the microcontroller into power saving mode
# when we get USB suspend event. We want it to keep updating
# backlight effects.
OPT_DEFS += -DNO_SUSPEND_POWER_DOWN

# Experimental features for zealcmd please do no enable
#RAW_ENABLE = yes
#USE_KEYMAPS_IN_EEPROM = yes
