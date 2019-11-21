ifdef MOUSEKEY_ENABLE
	SRC += mousekey_accel.c
endif

ifdef ENHANCED_SHIFT
	OPT_DEFS += -DENHANCED_SHIFT
	SRC += enhanced_shift.c
	TAPDANCE_ENABLE = yes
endif
