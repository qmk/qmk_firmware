SRC += scotto.c

TAP_DANCE_ENABLE = yes

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tap_dance.c
endif

ifneq ($(strip $(KEYMAP)),)
    OPT_DEFS += -DKEYMAP_$(KEYMAP)
endif
