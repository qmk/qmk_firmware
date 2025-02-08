ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    DFU_SUFFIX_ARGS = -v 3297 -p 2000
    DFU_ARGS = -d 3297:2000 -a 0 -s 0x08002000:leave
else ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    DFU_SUFFIX_ARGS = -v 3297 -p 2001
    DFU_ARGS = -d 3297:2001 -a 0 -s 0x08002000:leave
else
    DFU_SUFFIX_ARGS = -v 3297 -p 2002
    DFU_ARGS = -d 3297:2002 -a 0 -s 0x08002000:leave
endif

ifeq ($(strip $(BOOTLOADER)), custom)
    MCU_LDSCRIPT = ergodox_ez
    PROGRAM_CMD = $(call EXEC_DFU)
else
    # boards ship with ignition but for drashna's sanity during testing, we'll
    # make sure that we can use stm32-dfu as well
    DFU_SUFFIX_ARGS = -v 0483 -p df11
    DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave
endif
