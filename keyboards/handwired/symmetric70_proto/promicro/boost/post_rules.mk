include $(strip $(KEYBOARD_LOCAL_OPTIONS_MK))

ifneq ($(findstring symmetric70_proto/promicro,$(KEYBOARD)),)
    CUSTOM_MATRIX = yes
    SRC += matrix_common.c
    SRC += matrix_boost/matrix.c
    ifeq ($(strip $(CANCEL_BOOST)),yes)
        OPT_DEFS += -DCANCEL_BOOST
    else
        SRC += users/mtei/matrix_read_cols_on_row.c
    endif
endif

