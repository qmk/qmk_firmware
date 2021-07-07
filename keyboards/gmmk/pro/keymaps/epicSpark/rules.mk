VIA_ENABLE = no

RGB_MATRIX_LEDMAPS = yes
COMBO_ENABLE = yes
WPM_ENABLE = no

ifeq ($(strip $(RGB_MATRIX_LEDMAPS)), yes)
	SRC += rgb_matrix_ledmaps.c
	OPT_DEFS += -DRGB_MATRIX_LEDMAPS_ENABLED
endif