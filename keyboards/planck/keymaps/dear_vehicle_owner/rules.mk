ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
DEBOUNCE_TYPE = sym_eager_pk
