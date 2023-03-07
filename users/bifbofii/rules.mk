SRC += bifbofii.c \
    callbacks.c \
    keyrecords/keycodes.c

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
	SRC += rgblights.c
endif

UNICODEMAP_ENABLE ?= yes

CONSOLE_DEBUG ?= no
ifeq ($(strip $(CONSOLE_DEBUG)), yes)
    CONSOLE_ENABLE = yes
    OPT_DEFS += -DCONSOLE_DEBUG
endif

TRI_LAYER_ENABLE ?= yes

GAMING_ENABLE ?= no
ifeq ($(strip $(GAMING_ENABLE)), yes)
    OPT_DEFS += -DGAMING_ENABLE
endif
