VIA_ENABLE = yes
ENCODER_MAP_ENABLE = yes
CAPS_WORD_ENABLE = yes
AUTOCORRECT_ENABLE = no

SRC += keymap_user_config.c

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    SRC += rgb_matrix_user.c
endif

VPATH += keyboards/keychron/common
SRC += keychron_common.c
