SRC += wanleg.c tapdances.c

TAP_DANCE_ENABLE = yes
MOUSEKEY_ENABLE = yes

#If using a ProMicro and it has the QMK DFU bootloader instead of Caterina,
#run "make <keyboard>:<keymap> dfu=qmk" when compiling to ensure it is flagged properly after being flashed
ifeq ($(strip $(dfu)), qmk)
    BOOTLOADER = qmk-dfu
endif

#use alternate settings for boards using ProMicro instead of Micro
#example usage: make 4x4:wanleg PM=yes
ifeq ($(strip $(PM)), yes)
	OPT_DEFS += -DPRO_MICRO
endif
