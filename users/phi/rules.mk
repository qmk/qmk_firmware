SRC += phi.c

ifdef CUSTOM_MOUSEKEY
	OPT_DEFS += -DCUSTOM_MOUSEKEY
	SRC += custom_mousekey.c
	MOUSEKEY_ENABLE = yes
endif

ifdef HSVDUMP
	SRC += hsvdump.c
endif
