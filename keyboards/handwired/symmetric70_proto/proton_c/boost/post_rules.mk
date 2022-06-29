include $(strip $(KEYBOARD_LOCAL_OPTIONS_MK))

ifneq ($(filter yes,$(MATRIX_DEBUG_SCAN) $(MATRIX_DEBUG_DELAY)),)
    CUSTOM_MATRIX = yes
    SRC += matrix_common.c
    SRC += matrix_boost/matrix.c
endif
