SRC += wanleg.c tapdances.c

ifndef TAP_DANCE_ENABLE
    TAP_DANCE_ENABLE = yes
endif


#If using a ProMicro and it has the QMK DFU bootloader instead of Caterina,
#run "make <keyboard>:<keymap> dfu=qmk" when compiling to ensure it is flagged properly after being flashed
ifeq ($(strip $(dfu)), qmk)
    BOOTLOADER = qmk-dfu
endif