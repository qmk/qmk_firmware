
SRC += drashna.c
EXTRAFLAGS        += -flto

ifneq ("$(wildcard users/$(KEYMAP)/config.h)","")
    CONFIG_H += users/$(KEYMAP)/config.h
endif

ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif
