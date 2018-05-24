
SRC += drashna.c
EXTRAFLAGS        += -flto

ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif

ifeq ($(strip $(INDICATOR_LIGHTS)), yes)
    OPT_DEFS += -DINDICATOR_LIGHTS
endif
