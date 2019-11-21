SRC += phi.c

ifdef CUSTOM_MOUSEKEY
	OPT_DEFS += -DCUSTOM_MOUSEKEY
	SRC += custom_mousekey.c
	MOUSEKEY_ENABLE = yes
endif

ifdef ENHANCED_SHIFT
	OPT_DEFS += -DENHANCED_SHIFT
	SRC += enhanced_shift.c
	TAPDANCE_ENABLE = yes
endif
