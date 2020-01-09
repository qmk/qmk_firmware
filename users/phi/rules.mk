SRC += phi.c

ifdef CUSTOM_MOUSEKEY
	OPT_DEFS += -DCUSTOM_MOUSEKEY
	SRC += custom_mousekey.c
	MOUSEKEY_ENABLE = yes
endif

ifdef MICROWRITER_KEYS
	OPT_DEFS += -DMICROWRITER_KEYS
	SRC += microwriter.c
endif

ifdef HSVDUMP
	OPT_DEFS += -HSVDUMP_KEYS
	SRC += hsvdump.c
endif
