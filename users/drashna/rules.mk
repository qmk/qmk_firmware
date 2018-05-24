
SRC += drashna.c
EXTRAFLAGS        += -flto

ifneq ("$(wildcard users/$(KEYMAP)/config.h)","")
    CONFIG_H += users/$(KEYMAP)/config.h
endif

ifeq ($(strip $(INDICATOR_LIGHTS)), yes)
    OPT_DEFS += -DINDICATOR_LIGHTS
endif
