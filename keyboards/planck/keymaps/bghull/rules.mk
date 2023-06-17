ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
AUTO_SHIFT_ENABLE = yes
MOUSEKEY_ENABLE = yes
AUDIO_ENABLE = no
COMBO_ENABLE = yes
VPATH += keyboards/gboards