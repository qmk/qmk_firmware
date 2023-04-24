#Anything that says ENABLED is not part of standard QMK
#these custom ones will need to be added to OPT_DEFS

SRC += $(USER_PATH)/T4CORUN.c \
		$(USER_PATH)/tapping.c \
		$(USER_PATH)/processor.c

TAP_DANCE_ENABLE ?= yes
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += $(USER_PATH)/tap_dances.c
endif

OLED_ENABLE ?= no
KEYLOG_ENABLED ?= no
ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += $(USER_PATH)/oled_stuff.c
	ifeq ($(strip $(KEYLOG_ENABLED)), yes)
	  OPT_DEFS += -DKEYLOG_ENABLED
	endif
endif

COMBO_ENABLE ?= yes
ifeq ($(strip $(COMBO_ENABLE)), yes)
	SRC += $(USER_PATH)/combos.c
endif

HOMEROWMOD_ENABLED ?= yes
ifeq ($(strip $(HOMEROWMOD_ENABLED)), yes)
  OPT_DEFS += -DHOMEROWMOD_ENABLED
endif

#AUTO_MOUSE_ENABLED is custom
POINTING_DEVICE_ENABLE ?= no
AUTOMOUSE_ENABLED ?= no
ifeq ($(strip $(POINTING_DEVICE_ENABLE)), yes)
	SRC += $(USER_PATH)/pointing.c
	OPT_DEFS += -DMOUSELAYER_ENABLED
	ifeq ($(strip $(AUTOMOUSE_ENABLED)), yes)
	  OPT_DEFS += -DAUTOMOUSE_ENABLED
	endif
endif

MOUSEKEY_ENABLE ?= no
ifeq ($(strip $(MOUSEKEY_ENABLE)), yes)
	OPT_DEFS += -DMOUSELAYER_ENABLED
endif

RGB_MATRIX_ENABLE ?=no
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC += $(USER_PATH)/rgb_matrix_stuff.c
endif


SPACE_CADET_ENABLE ?= no
GRAVE_ESC_ENABLE ?= no
DYNAMIC_MACRO_ENABLE ?= yes
LTO_ENABLE ?= yes
MAGIC_ENABLE ?= no