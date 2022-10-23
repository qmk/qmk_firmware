COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
# TAP_HOLD_ENABLE = no

SRC += jugemu.c \
	modes.c	\
	keycodes.c \
	init.c

SRC += tap_hold.c

ifeq ($(strip $(COMBO_ENABLE)), yes)
	SRC += custom_combo.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += custom_tap_dance.c
endif

# ifeq ($(strip $(TAP_HOLD_ENABLE)), yes)
# 	SRC += tap_hold.c
# endif
