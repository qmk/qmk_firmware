CUSTOM_MATRIX = lite
ANALOG_DRIVER_REQUIRED = yes
VPATH += keyboards/cipulot/common
SRC += matrix.c ec_board.c ec_switch_matrix.c

ifeq ($(strip $(VIA_ENABLE)), yes)
    SRC += via_ec.c
endif
