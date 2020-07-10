SRC += pcoves.c

RAINBOW_UNICORN_ENABLE ?= no
ifneq ($(strip $(RAINBOW_UNICORN_ENABLE)), no)
	SRC += rainbowUnicorn.c
	OPT_DEFS += -DRAINBOW_UNICORN_ENABLE
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tapDance.c
endif

ifeq ($(strip $(COMBO_ENABLE)), yes)
    SRC += combo.c
endif

ifeq ($(strip $(UNICODE_ENABLE)), yes)
    SRC += unicode.c
	OPT_DEFS += -DUNICODE_ENABLE
endif

ifneq ($(strip $(NO_SECRET)), yes)
    ifneq ("$(wildcard $(USER_PATH)/secret.c)","")
        SRC += secret.c
	else
		OPT_DEFS += -DNO_SECRET
    endif
else
	OPT_DEFS += -DNO_SECRET
endif
