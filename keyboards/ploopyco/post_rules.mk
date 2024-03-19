OPT_ENCODER_TYPE ?= default
VALID_OPT_ENCODER_TYPES := default simple tiny custom

ifeq ($(filter $(OPT_ENCODER_TYPE),$(VALID_OPT_ENCODER_TYPES)),)
    $(call CATASTROPHIC_ERROR,Invalid OPT_ENCODER_TYPE,OPT_ENCODER_TYPE="$(OPT_ENCODER_TYPE)" is not a valid pointing device type)
else
    ifneq ($(strip $(OPT_ENCODER_TYPE)), custom)
        VPATH += keyboards/ploopyco/common
        SRC += opt_encoder_$(strip $(OPT_ENCODER_TYPE)).c
        ANALOG_DRIVER_REQUIRED = yes
    endif
endif
