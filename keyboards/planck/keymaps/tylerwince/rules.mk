ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
LTO_ENABLE = yes
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
TAP_DANCE_ENABLE=yes
