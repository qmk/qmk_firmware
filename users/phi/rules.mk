SRC += phi.c

ifdef MICROWRITER_KEYS
	OPT_DEFS += -DMICROWRITER_KEYS
	SRC += microwriter.c
endif

ifdef HSVDUMP
	OPT_DEFS += -HSVDUMP_KEYS
	SRC += hsvdump.c
endif
