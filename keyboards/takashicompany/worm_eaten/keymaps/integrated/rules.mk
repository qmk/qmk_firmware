SPLIT_KEYBOARD = no
INTEGRATED = yes
VIA_ENABLE = yes

ifeq ($(strip $(INTEGRATED)), yes)
    OPT_DEFS += -DINTEGRATED
endif