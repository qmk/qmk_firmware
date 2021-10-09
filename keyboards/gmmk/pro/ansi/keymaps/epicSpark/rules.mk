VIA_ENABLE = no

RGB_MATRIX_LEDMAPS = yes
WPM_ENABLE = no
TAP_DANCE_ENABLE = yes

# I think this has something to do with the compiler :)
ifeq ($(strip $(RGB_MATRIX_LEDMAPS)), yes)
	SRC += rgb_matrix_ledmaps.c
	OPT_DEFS += -DRGB_MATRIX_LEDMAPS_ENABLED
endif