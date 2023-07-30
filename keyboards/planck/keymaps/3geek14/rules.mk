ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
    SRC += muse_mode.c
endif
SRC += tap_dance.c

CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = yes
UNICODE_COMMON = yes

# Firmware size optimizations:
LTO_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
