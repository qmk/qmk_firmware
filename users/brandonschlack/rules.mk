SRC += brandonschlack.c \
       process_records.c

ifeq ($(strip $(BOOTLOADER)), mdloader)
    OPT_DEFS += -DBOOTLOADER_MDLOADER
    DISABLE_LTO = yes
endif

ifneq ($(strip $(DISABLE_LTO)), yes)
  EXTRAFLAGS += -flto
  OPT_DEFS += -DLINK_TIME_OPTIMIZATION_ENABLE
  OPT_DEFS += -DNO_ACTION_MACRO
  OPT_DEFS += -DNO_ACTION_FUNCTION
endif

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
