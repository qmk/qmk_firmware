SRC += klackygears.c

#EXTRAFLAGS += -flto  compiles, does weird things to the helix


ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
  SRC += tap_dances.c
endif



##ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
##  SRC += rgb_stuff.c
##  ifeq ($(strip $(RGBLIGHT_EFFECT_BEAM)), yes)
##      OPT_DEFS += -DRGBLIGHT_EFFECT_BEAM
##  endif
##  ifeq ($(strip $(RGBLIGHT_EFFECT_HYPER)), yes)
##    OPT_DEFS += -DRGBLIGHT_EFFECT_HYPER
##  endif
##  ifeq ($(strip $(RGBLIGHT_EFFECT_RAINBOW_SPARKLE)), yes)
##    OPT_DEFS += -DRGBLIGHT_EFFECT_RAINBOW_SPARKLE
##  endif
##endif


ifeq ($(strip $(MACROS_ENABLED)), yes)
    OPT_DEFS += -DMACROS_ENABLED
endif
