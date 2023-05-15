#Anything that says ENABLED is not part of standard QMK
#these custom ones will need to be added to OPT_DEFS

SRC += $(USER_PATH)/T4CORUN.c \
		$(USER_PATH)/tapping.c \
		$(USER_PATH)/processor.c

TAP_DANCE_ENABLE ?= no
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += $(USER_PATH)/tap_dance.c
endif

OLED_ENABLE ?= no
KEYLOG_ENABLE ?= no
ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += $(USER_PATH)/oled_stuff.c
	ifeq ($(strip $(KEYLOG_ENABLE)), yes)
	  OPT_DEFS += -DKEYLOG_ENABLE
	endif
endif


COMBO_ENABLE ?= no
ifeq ($(strip $(COMBO_ENABLE)), yes)
	SRC += $(USER_PATH)/combo.c
endif

HOMEROWMOD_ENABLE ?= yes
ifeq ($(strip $(HOMEROWMOD_ENABLE)), yes)
  OPT_DEFS += -DHOMEROWMOD_ENABLE
endif

#AUTOMOUSE_ENABLE is custom
POINTING_DEVICE_ENABLE ?= no
AUTOMOUSE_ENABLE ?= no
ifeq ($(strip $(POINTING_DEVICE_ENABLE)), yes)
	SRC += $(USER_PATH)/pointing.c
	OPT_DEFS += -DMOUSELAYER_ENABLE
	ifeq ($(strip $(AUTOMOUSE_ENABLED)), yes)
	  OPT_DEFS += -DAUTOMOUSE_ENABLE
	endif
endif

MOUSEKEY_ENABLE ?= no
ifeq ($(strip $(MOUSEKEY_ENABLE)), yes)
	OPT_DEFS += -DMOUSELAYER_ENABLE
endif

RGB_MATRIX_ENABLE ?=no
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC += $(USER_PATH)/rgb_matrix_stuff.c
endif

#GAMING_ENABLED is custom
GAMELAYER_ENABLE ?=no
ifeq ($(strip $(GAMELAYER_ENABLE)), yes)
	OPT_DEFS += -DGAMELAYER_ENABLE
endif


SPACE_CADET_ENABLE ?= no
GRAVE_ESC_ENABLE ?= no
DYNAMIC_MACRO_ENABLE ?= yes
LTO_ENABLE ?= yes
MAGIC_ENABLE ?= no