
SRC += milestogo.c

COMBO_ENABLE=yes
VPATH += keyboards/gboards

UNICODEMAP_ENABLE=yes

USE_BABBLEPASTE = yes
VPATH += users/milestogo/babblepaste

ifeq ($(strip $(USE_BABBLEPASTE)), yes)
	## comment out modes you wont use to save space
	SRC += babblepaste.c 
	SRC += babl_mac.c babl_linux.c babl_readmux.c 
	SRC += babl_windows.c babl_chromeos.c 
	SRC += babl_emacs.c babl_kitty.c babl_nano.c babl_vi.c 
	SRC += babl_select.c
endif
