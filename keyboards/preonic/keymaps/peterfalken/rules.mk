# Setup keymap QMK features
# TODO: Check for space optimizations
AUDIO_ENABLE = yes      # Enable Audio Output
ENCODER_ENABLE = no     # Disable encoder

ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
