COMBO_ENABLE		= yes
CONSOLE_ENABLE		= yes

SRC += ibnuda.c

ifeq ($(strip $(COMBO_ENABLE)), yes)
	SRC += combo.c
endif
