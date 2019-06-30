SRC += klackygears.c

#EXTRAFLAGS += -flto  compiles, does weird things to the helix


ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
  SRC += tap_dances.c
endif


# ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
#     SRC += rgb_fun.c
# endif


ifeq ($(strip $(MACROS_ENABLED)), yes)
    OPT_DEFS += -DMACROS_ENABLED
endif

#ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
#  SRC += rgblight.c
#endif
