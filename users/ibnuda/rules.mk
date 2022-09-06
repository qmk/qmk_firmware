COMBO_ENABLE		= yes
COMMAND_ENABLE		= yes
CONSOLE_ENABLE		= yes
TAP_DANCE_ENABLE	= yes

SRC += ibnuda.c

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += tapdance.c
endif

ifeq ($(strip $(COMBO_ENABLE)), yes)
	SRC += combo.c
endif
