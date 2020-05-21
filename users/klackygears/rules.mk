SRC += klackygears.c

#EXTRAFLAGS += -flto  compiles, does weird things to the helix


ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
  SRC += tap_dances.c
endif

ifeq ($(strip $(MACROS_ENABLED)), yes)
    OPT_DEFS += -DMACROS_ENABLED
endif
