# Path: keyboards/rephlex/2k/rules.mk
QUANTUM_LIB_SRC += analog.c
SRC += matrix.c lut.c scanfunctions.c

DEFERRED_EXEC_ENABLE = yes
CUSTOM_MATRIX = lite

OPT = 3