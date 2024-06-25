MCU_LDSCRIPT = ergodox_ez
PROGRAM_CMD = $(call EXEC_DFU)
DFU_ARGS = -d 3297:2001 -a 0 -s 0x08002000:leave
DFU_SUFFIX_ARGS = -v 3297 -p 2001

DEFAULT_FOLDER = zsa/ergodox_ez/gd32/base
