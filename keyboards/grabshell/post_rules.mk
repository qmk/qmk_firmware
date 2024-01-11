# Build Options
#   change yes to no to disable
#
# If MIDI_ENABLE is 'yes', set the following parameters to 'no'
ifeq ($(strip $(MIDI_ENABLE)), yes)
CONSOLE_ENABLE = no
NKRO_ENABLE = no
EXTRAKEY_ENABLE = no
MOUSEKEY_ENABLE = no
endif
