SRC += gourdo1.c
SRC += autocorrect/autocorrection.c

ifdef ENCODER_ENABLE
	# include encoder related code when enabled
	ifeq ($(strip $(ENCODER_DEFAULTACTIONS_ENABLE)), yes)
		OPT_DEFS += -DENCODER_DEFAULTACTIONS_ENABLE
	endif
	ifeq ($(strip $(ALTTAB_SCROLL_ENABLE)), yes)
		OPT_DEFS += -DALTTAB_SCROLL_ENABLE
	endif
	SRC += gourdo1_encoder.c
endif
ifeq ($(strip $(TD_LSFT_CAPSLOCK_ENABLE)), yes)
    OPT_DEFS += -DTD_LSFT_CAPSLOCK_ENABLE
endif
ifeq ($(strip $(IDLE_TIMEOUT_ENABLE)), yes)
    OPT_DEFS += -DIDLE_TIMEOUT_ENABLE
endif
ifeq ($(strip $(STARTUP_NUMLOCK_ON)), yes)
    OPT_DEFS += -DSTARTUP_NUMLOCK_ON
endif
ifeq ($(strip $(COLEMAK_LAYER_ENABLE)), yes)
    OPT_DEFS += -DCOLEMAK_LAYER_ENABLE
endif
ifeq ($(strip $(EMOTICON_ENABLE)), yes)
    OPT_DEFS += -DEMOTICON_ENABLE
endif
ifeq ($(strip $(INVERT_NUMLOCK_INDICATOR)), yes)
    OPT_DEFS += -DINVERT_NUMLOCK_INDICATOR
endif
