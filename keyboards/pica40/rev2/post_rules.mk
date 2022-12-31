# if ENCODER_ENABLE is set, add defines but avoid adding encoder.c as it's replaced by custom code in rev2.c
ifeq ($(strip $(ENCODER_ENABLE)), yes)
	ENCODER_ENABLE := no
    OPT_DEFS += -DENCODER_ENABLE
    ifeq ($(strip $(ENCODER_MAP_ENABLE)), yes)
        OPT_DEFS += -DENCODER_MAP_ENABLE
    endif
endif
