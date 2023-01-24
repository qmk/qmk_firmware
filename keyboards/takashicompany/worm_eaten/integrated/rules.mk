SPLIT_KEYBOARD = no
INTEGRATED = yes

ifeq ($(strip $(INTEGRATED)), yes)
    OPT_DEFS += -DINTEGRATED
endif