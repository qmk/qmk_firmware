
SRC += drashna.c


ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
  SRC += tap_dances.c
endif

EXTRAFLAGS        += -flto

ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
else
  SRC += secrets.c
endif

ifeq ($(strip $(INDICATOR_LIGHTS)), yes)
    OPT_DEFS += -DINDICATOR_LIGHTS
endif

ifeq ($(strip $(MACROS_ENABLED)), yes)
    OPT_DEFS += -DMACROS_ENABLED
endif
