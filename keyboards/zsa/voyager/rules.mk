MCU_LDSCRIPT = voyager

CUSTOM_MATRIX = lite
PROGRAM_CMD = $(call EXEC_DFU)
DFU_ARGS = -d 3297:0791 -a 0 -s 0x08002000:leave
DFU_SUFFIX_ARGS = -v 3297 -p 0791

SRC += matrix.c
QUANTUM_LIB_SRC += i2c_master.c
