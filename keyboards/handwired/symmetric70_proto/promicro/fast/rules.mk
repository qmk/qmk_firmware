VPATH += users/mtei
VPATH += users/mtei/$(PLATFORM_PATH)
VPATH += users/mtei/$(PLATFORM_PATH)/$(PLATFORM_KEY)

CUSTOM_MATRIX = yes
SRC += matrix_common.c
SRC += matrix_fast/matrix.c
