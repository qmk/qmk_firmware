ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif

BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MIDI_ENABLE = no
AUDIO_ENABLE = yes
RGBLIGHT_ENABLE = no
TAP_DANCE_ENABLE = yes
LEADER_ENABLE = yes
