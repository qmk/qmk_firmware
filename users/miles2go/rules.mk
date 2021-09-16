SRC += milestogo.c  babblePaste.c babl_mac.c babl_linux.c

ifeq ($(strip $(USE_BABBLEPASTE)), yes)
	SRC += babblePaste.c
endif
