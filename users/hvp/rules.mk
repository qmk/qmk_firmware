
SRC += hvp.c
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
     SRC += tap_dances.c
endif

ifeq ($(strip $(TAPPING_TERM_PER_KEY)), yes)
     SRC += per_key.c
endif