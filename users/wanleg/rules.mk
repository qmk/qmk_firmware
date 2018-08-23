ifeq ($(strip $(KEYBOARD)), lets_split_rev2)
SRC += ../../keyboards/lets_split/lets_split.c
endif

SRC += wanleg.c tapdances.c 

TAP_DANCE_ENABLE = yes
MOUSEKEY_ENABLE = yes

#If using a ProMicro and it has the QMK DFU bootloader instead of Caterina,
#run "make <keyboard>:<keymap> dfu=qmk" when compiling to ensure it is flagged properly after being flashed
ifeq ($(strip $(dfu)), qmk)
    BOOTLOADER = qmk-dfu
endif
