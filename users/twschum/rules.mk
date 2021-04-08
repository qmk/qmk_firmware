SRC += twschum.c
SRC += xtonhasvim.c
ifeq ($(strip $(FLASH_BOOTLOADER)), yes)
    OPT_DEFS += -DFLASH_BOOTLOADER
endif
