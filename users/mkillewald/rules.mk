RAW_ENABLE = no
VIA_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes

SRC += mkillewald.c
SRC += eeprom_user_config.c
SRC += myfork_keychron_ft.c

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    SRC += rgb_matrix_user.c
endif