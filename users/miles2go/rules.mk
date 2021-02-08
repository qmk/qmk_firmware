SRC += milestogo.c  babblePaste.c babl_windows.c babl_mac.c babl_vi.c babl_readmux.c  babl_chromeos.c babl_emacs.c babl_linux.c
LTO_ENABLE = yes

ifeq ($(strip $(MACROS_ENABLED)), yes)
    OPT_DEFS += -DMACROS_ENABLED
endif

ifeq ($(strip $(USE_BABBLEPASTE)), yes)
	SRC += babblePaste.c
endif
