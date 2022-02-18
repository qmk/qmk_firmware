VIA_ENABLE = yes
MOUSEKEY_ENABLE = no
TAP_DANCE_ENABLE = yes

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    SRC += rgb_matrix_user.c
endif
