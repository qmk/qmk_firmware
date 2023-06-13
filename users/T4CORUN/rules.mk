SRC += $(USER_PATH)/T4CORUN.c \
		$(USER_PATH)/features/tapping.c

SPACE_CADET_ENABLE ?= no
GRAVE_ESC_ENABLE ?= no
DYNAMIC_MACRO_ENABLE ?= yes
LTO_ENABLE ?= yes
MAGIC_ENABLE ?= no


CAPS_WORD_ENABLE ?= yes
ifeq ($(strip $(CAPS_WORD_ENABLE)), yes)
	SRC += $(USER_PATH)/features/capsword.c
endif


TAP_DANCE_ENABLE ?= no
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += $(USER_PATH)/features/tapdance.c
endif

OLED_ENABLE ?= no
#KEYLOG_ENABLE appears to be custom
KEYLOG_ENABLE ?= no
ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += $(USER_PATH)/features/oled.c
	ifeq ($(strip $(KEYLOG_ENABLE)), yes)
	  OPT_DEFS += -DKEYLOG_ENABLE
	endif
endif


COMBO_ENABLE ?= no
ifeq ($(strip $(COMBO_ENABLE)), yes)
#	SRC += $(USER_PATH)/combo.c
	INTROSPECTION_KEYMAP_C = $(USER_PATH)/features/combo.c
endif

#HOMEROWMOD_ENABLE is custom
HOMEROWMOD_ENABLE ?= yes
ifeq ($(strip $(HOMEROWMOD_ENABLE)), yes)
  OPT_DEFS += -DHOMEROWMOD_ENABLE
endif

#AUTOMOUSE_ENABLE is custom
POINTING_DEVICE_ENABLE ?= no
AUTOMOUSE_ENABLE ?= no
ifeq ($(strip $(POINTING_DEVICE_ENABLE)), yes)
	SRC += $(USER_PATH)/features/mouse.c
	OPT_DEFS += -DMOUSELAYER_ENABLE
	ifeq ($(strip $(AUTOMOUSE_ENABLED)), yes)
	  OPT_DEFS += -DAUTOMOUSE_ENABLE
	endif
endif

MOUSEKEY_ENABLE ?= no
ifeq ($(strip $(MOUSEKEY_ENABLE)), yes)
	OPT_DEFS += -DMOUSELAYER_ENABLE
endif

RGB_MATRIX_ENABLE ?= no
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC += $(USER_PATH)/features/rgbmatrix.c
endif

#GAMING_ENABLED is custom
GAMELAYER_ENABLE ?= no
ifeq ($(strip $(GAMELAYER_ENABLE)), yes)
	OPT_DEFS += -DGAMELAYER_ENABLE
endif

#ONESHOT_ENABLED is custom
ONESHOT_ENABLE ?= no
ifeq ($(strip $(ONESHOT_ENABLE)), yes)
	OPT_DEFS += -DONESHOT_ENABLE
endif