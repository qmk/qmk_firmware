SRC += brandonschlack.c \
       process_records.c

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += rgb_bs.c
endif

RGB_MATRIX_ENABLE ?= no
ifneq ($(strip $(RGB_MATRIX_ENABLE)), no)
    SRC += rgb_bs.c
endif

ifeq ($(strip $(FLASH_BOOTLOADER)), yes)
    OPT_DEFS += -DFLASH_BOOTLOADER
endif

ifeq ($(strip $(IS_MACROPAD)), yes)
    OPT_DEFS += -DIS_MACROPAD
endif
