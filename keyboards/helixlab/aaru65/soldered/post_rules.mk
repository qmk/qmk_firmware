ifeq ($(strip $(RGB_INDICATOR_ENABLE)),yes)
	OPT_DEFS += -DRGB_INDICATOR_ENABLE
	SRC += \
		aw2023.c \
		rgb_indicator.c
endif