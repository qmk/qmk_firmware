SRC += brandonschlack.c \
       process_records.c

SPACE_CADET_ENABLE = no

# Use LTO except for ChibiOS
ifneq ($(PLATFORM),CHIBIOS)
    LTO_ENABLE            = yes
endif

ifeq ($(strip $(IS_MACROPAD)), yes)
    OPT_DEFS += -DIS_MACROPAD
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += rgb_bs.c
endif

RGB_MATRIX_ENABLE ?= no
ifneq ($(strip $(RGB_MATRIX_ENABLE)), no)
    SRC += rgb_bs.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tap_dances.c
endif

ifeq ($(strip $(FLASH_BOOTLOADER)), yes)
    OPT_DEFS += -DFLASH_BOOTLOADER
endif

ifneq ($(FORCE_LAYOUT),)
    OPT_DEFS += -DFORCE_LAYOUT=\"$(FORCE_LAYOUT)\"
endif
