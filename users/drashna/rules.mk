
SRC += drashna.c
EXTRAFLAGS        += -flto

ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif
