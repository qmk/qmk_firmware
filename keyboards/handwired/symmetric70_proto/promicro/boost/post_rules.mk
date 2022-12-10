KEYBOARD_LOCAL_OPTIONS_MK := $(dir $(lastword $(MAKEFILE_LIST)))../../local_options.mk
include $(strip $(KEYBOARD_LOCAL_OPTIONS_MK))

ifneq ($(filter yes,$(MATRIX_DEBUG_SCAN) $(MATRIX_DEBUG_DELAY)),)
    CUSTOM_MATRIX = yes
    SRC += matrix_common.c
    SRC += matrix_boost/matrix.c
endif

ifneq ($(findstring symmetric70_proto/promicro,$(KEYBOARD)),)
    # The symmetric70_proto/promicro hardware uses 74hc157,
    # so you need software to operate it.
    ifeq ($(strip $(CANCEL_BOOST)),yes)
        OPT_DEFS += -DCANCEL_BOOST
        SRC += matrix_boost/matrix_extension_74hc157.c
    else
        SRC += users/mtei/matrix_boost/matrix_read_cols_on_row.c
    endif
endif

