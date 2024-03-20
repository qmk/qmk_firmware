VIA_ENABLE = yes
RGB_MATRIX_CUSTOM_USER = yes

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    SRC += $(USER_PATH)/horrortroll.c
endif
