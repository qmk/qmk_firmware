ifneq ($(strip $(OPT_ENCODER_TYPE)), custom)
	SRC += opt_encoder_$(strip $(OPT_ENCODER_TYPE)).c
endif
