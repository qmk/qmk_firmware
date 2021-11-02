SRC += jdelkins.c

ifneq ($(strip $(NO_SECRETS)),)
	OPT_DEFS += -DNO_SECRETS
endif

ifeq ($(shell test -f users/jdelkins/secrets.h.gpg && echo yes || echo no),yes)
users/jdelkins/jdelkins.c: users/jdelkins/secrets.h
	touch $@

users/jdelkins/secrets.h: users/jdelkins/secrets.h.gpg
	gpg -d $< >$@
endif

BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
