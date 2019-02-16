# This gets included at the beginning of the Planck's Makefile.
# Alternatively, you can run make from the keymap directory
# and the main Makefile will be included after.

COMMAND_ENABLE   = no   # Disable shift combination, which conflicts with shift-parens
NKRO_ENABLE      = yes  # N-key rollover required for use as a steno board
AUDIO_ENABLE     = no   # Audio output on port C6
TAP_DANCE_ENABLE = yes
MOUSEKEY_ENABLE  = yes
CONSOLE_ENABLE = no
BACKLIGHT_ENABLE = yes


SPACE_CADET_ENABLE = yes  # add option for PR #3885, space cadet feature is going to disable default.
