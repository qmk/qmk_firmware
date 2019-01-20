TAP_DANCE_ENABLE = yes
SRC += klackygears.c

EXTRAFLAGS += -flto


##ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
##  SRC += tap_dances.c
##endif
