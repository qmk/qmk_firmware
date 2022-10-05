COMBO_ENABLE = yes

SRC += jugemu.c

ifeq ($(strip $(COMBO_ENABLE)), yes)
	SRC += combo.c
endif

# ifeq ($(strip $(WPM_ENABLE)), yes)
# 	ifeq ($(strip $(OLED_ENABLE)), yes)
# 		SRC += oled.c
# 	endif
# endif
