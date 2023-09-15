ifeq ($(strip $(JOYSTICK_ENABLE)), yes)
	SRC += $(USER_PATH)/gamepad.c
endif

ifeq ($(strip $(TAIPO_ENABLE)), yes)
	SRC += $(USER_PATH)/taipo.c
	OPT_DEFS += -DTAIPO_ENABLE
endif
