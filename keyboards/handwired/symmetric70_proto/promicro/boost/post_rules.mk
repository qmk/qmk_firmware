include $(strip $(KEYBOARD_LOCAL_OPTIONS_MK))

ifneq ($(findstring symmetric70_proto/promicro,$(KEYBOARD)),)
    CUSTOM_MATRIX = yes
    SRC += matrix_common.c
    SRC += matrix_boost/matrix.c
endif

