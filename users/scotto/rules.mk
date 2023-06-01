SRC += scotto.c tap_dance.c

TAP_DANCE_ENABLE = yes

ifneq ($(strip $(KEYMAP)),)
  OPT_DEFS += -DKEYMAP_$(KEYMAP)
endif