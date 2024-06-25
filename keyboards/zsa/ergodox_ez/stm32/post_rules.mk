ifeq ($(strip $(BOOTLOADER)), custom)
    MCU_LDSCRIPT = ergodox_ez
    PROGRAM_CMD = $(call EXEC_DFU)
else
    # boards ship with ignition but for drashna's sanity during testing, we'll
    # make sure that we can use stm32-dfu as well
    DFU_SUFFIX_ARGS = -v 0483 -p df11
    DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave
endif
