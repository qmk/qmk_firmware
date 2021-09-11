COMBO_ENABLE = yes
COMMAND_ENABLE = yes
CONSOLE_ENABLE = yes
EXTRAKEY_ENABLE = yes          # Audio control and System control
MOUSEKEY_ENABLE = no
RAW_ENABLE = no
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_LEDMAPS = yes
STARTUP_NUMLOCK_ON = yes
UNICODE_ENABLE = yes
VIA_ENABLE = no
WPM_ENABLE = no

SRC += utils.c eajaysec.c process_record.c encoder.c

ifeq ($(strip $(WPM_ENABLE)), yes)
	SRC += fun.c
endif

ifeq ($(strip $(RGB_MATRIX_LEDMAPS)), yes)
	SRC += rgb_matrix_ledmaps.c
	OPT_DEFS += -DRGB_MATRIX_LEDMAPS_ENABLED
endif
