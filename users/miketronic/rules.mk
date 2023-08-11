SRC += miketronic.c process_records.c
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += $(USER_PATH)/tapdances.c
endif
