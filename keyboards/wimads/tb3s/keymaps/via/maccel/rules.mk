ifeq ($(strip $(MACCEL_ENABLE)), yes)
	SRC += $(USER_PATH)/features/maccel/maccel.c
	ifeq ($(strip $(VIA_ENABLE)), yes)
		ifeq ($(strip $(MACCEL_VIA_ENABLE)), yes)
			SRC += $(USER_PATH)/features/maccel/maccel_via.c
		endif
	endif
	OPT_DEFS += -DMACCEL_ENABLE
endif
