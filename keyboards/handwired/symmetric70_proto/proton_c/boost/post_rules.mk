KEYBOARD_LOCAL_OPTIONS_MK := $(dir $(lastword $(MAKEFILE_LIST)))../../local_options.mk
include $(strip $(KEYBOARD_LOCAL_OPTIONS_MK))

ifneq ($(filter yes,$(MATRIX_DEBUG_SCAN) $(MATRIX_DEBUG_DELAY)),)
    CUSTOM_MATRIX = yes
    SRC += matrix_common.c
    SRC += matrix_boost/matrix.c
endif

ifeq ($(strip $(CANCEL_BOOST)),yes)
    OPT_DEFS += -DCANCEL_BOOST
else
    SRC += users/mtei/matrix_read_cols_on_row.c
endif
