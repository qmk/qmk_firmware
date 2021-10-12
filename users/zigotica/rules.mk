SRC += zigotica.c

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tapdances.c
endif

ifeq ($(strip $(COMBO_ENABLE)), yes)
    SRC += combos.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += oled.c
endif

