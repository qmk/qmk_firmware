SRC += brandonschlack.c \
       process_records.c

ifeq ($(strip $(BOOTLOADER)), mdloader)
    OPT_DEFS += -DBOOTLOADER_MDLOADER
else
    LINK_TIME_OPTIMIZATION_ENABLE = yes
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

ifdef RGB_THEME
    ifeq ($(strip $(RGB_THEME)), laser)
        OPT_DEFS += -DTHEME_LASER
    else ifeq ($(strip $(RGB_THEME)), granite)
        OPT_DEFS += -DTHEME_GRANITE
    endif
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tap_dances.c
endif

ifeq ($(strip $(FLASH_BOOTLOADER)), yes)
    OPT_DEFS += -DFLASH_BOOTLOADER
endif

