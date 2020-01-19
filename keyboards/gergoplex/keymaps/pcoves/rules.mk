VERBOSE                = no
DEBUG_MATRIX_SCAN_RATE = no
DEBUG_MATRIX           = no

SRC += matrix.c i2c_master.c
ifeq ($(strip $(DEBUG_MATRIX)), yes)
    OPT_DEFS += -DDEBUG_MATRIX
endif

COMBO_ENABLE           = yes
TAP_DANCE_ENABLE       = yes
UNICODE_ENABLE         = yes
