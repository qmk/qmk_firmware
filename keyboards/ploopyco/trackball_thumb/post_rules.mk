# Force encoder to be disabled
# But enable the defines for it
ENCODER_ENABLE := no
OPT_DEFS += -DENCODER_ENABLE

ifneq ($(strip $(OPT_ENCODER_TYPE)), custom)
	SRC += opt_encoder_$(strip $(OPT_ENCODER_TYPE)).c
endif
