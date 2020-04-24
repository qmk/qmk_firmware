# This gets included at the beginning of the Planck's Makefile.
# Alternatively, you can run make from the keymap directory
# and the main Makefile will be included after.

COMMAND_ENABLE   = no   # Disable shift combination, which conflicts with shift-parens
NKRO_ENABLE      = yes  # N-key rollover required for use as a steno board
AUDIO_ENABLE     = no   # Audio output (needs a pin configured in config.h, see docs/feature_audio.md)
TAP_DANCE_ENABLE = yes
MOUSEKEY_ENABLE  = yes
CONSOLE_ENABLE = no
BACKLIGHT_ENABLE = yes

