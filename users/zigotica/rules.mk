SRC += zigotica.c

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tapdances.c
endif
