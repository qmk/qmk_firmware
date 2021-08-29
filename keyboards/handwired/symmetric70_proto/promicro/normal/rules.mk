CUSTOM_MATRIX = yes
SRC += matrix_common.c
SRC += matrix_debug/matrix.c

KEYBOARD_LOCAL_FEATURES_MK := $(dir $(lastword $(MAKEFILE_LIST)))../../local_features.mk
include $(KEYBOARD_LOCAL_FEATURES_MK)
