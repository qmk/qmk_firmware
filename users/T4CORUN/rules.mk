SRC += $(USER_PATH)/T4CORUN.c \
		$(USER_PATH)/tapping.c

TAP_DANCE_ENABLE ?= no
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += $(USER_PATH)/tap_dances.c
endif

OLED_ENABLE ?= no
ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += $(USER_PATH)/oled_stuff.c
endif

COMBO_ENABLE ?= yes
ifeq ($(strip $(COMBO_ENABLE)), yes)
	SRC += $(USER_PATH)/combos.c
endif

KEYLOG_ENABLE ?= no
ifeq ($(strip $(KEYLOG_ENABLE)), yes)
    OPT_DEFS += -DKEYLOG_ENABLE
endif

ONESHOTKEY_ENABLE ?= no
ifeq ($(strip $(ONESHOTKEY_ENABLE)), yes)
    OPT_DEFS += -DONESHOTKEY_ENABLE
endif

HOMEROWMOD_ENABLE ?= yes
ifeq ($(strip $(HOMEROWMOD_ENABLE)), yes)
    OPT_DEFS += -DHOMEROWMOD_ENABLE
endif