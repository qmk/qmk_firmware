SRC += $(USER_PATH)/christrotter.c \
        $(USER_PATH)/callbacks.c \
        $(USER_PATH)/keyrecords/process_records.c \
        $(USER_PATH)/keyrecords/tapping.c \
		$(USER_PATH)/pointing/pointing.c

CUSTOM_RGB_MATRIX ?= yes
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    ifeq ($(strip $(CUSTOM_RGB_MATRIX)), yes)
        SRC += $(USER_PATH)/rgb/rgb_matrix_stuff.c
        OPT_DEFS += -DCUSTOM_RGB_MATRIX
    endif
endif