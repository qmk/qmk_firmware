# Processor frequency.
F_CPU = 8000000

# DEBOUNCE_TYPE = sym_defer_pk
CUSTOM_MATRIX = lite

VPATH += drivers/gpio
SRC += mcp23018.c matrix.c	   
QUANTUM_LIB_SRC += i2c_master.c