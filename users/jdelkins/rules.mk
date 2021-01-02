SRC += jdelkins.c

ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif

users/jdelkins/secrets.h: users/jdelkins/secrets.h.gpg
	gpg -d $< >$@

BOOTMAGIC_ENABLE = no
