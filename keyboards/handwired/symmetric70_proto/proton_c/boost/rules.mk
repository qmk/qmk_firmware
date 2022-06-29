VPATH += users/mtei/$(PLATFORM_PATH)
VPATH += users/mtei/$(PLATFORM_PATH)/$(PLATFORM_KEY)

ifeq ($(strip $(CANCEL_BOOST)),yes)
    OPT_DEFS += -DCANCEL_BOOST
else
    SRC += users/mtei/matrix_read_cols_on_row.c
endif
