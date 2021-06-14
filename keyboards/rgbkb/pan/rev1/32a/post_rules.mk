# As long as the users rules.mk has include $(KEYBOARD)/post_rules.mk this will be run after to properly setup any keyboard features and defines
ifeq ($(strip $(RGB_MATRIX_KEYPRESSES)), yes)
    OPT_DEFS += -DRGB_MATRIX_KEYPRESSES
endif

ifeq ($(strip $(RGB_MATRIX_FRAMEBUFFER)), yes)
    OPT_DEFS += -DRGB_MATRIX_FRAMEBUFFER_EFFECTS
endif

ifeq ($(strip $(STAGGERED_LAYOUT)), yes)
    OPT_DEFS += -DSTAGGERED_LAYOUT
endif

ifeq ($(strip $(RGB_ENCODERS)), yes)
    OPT_DEFS += -DRGB_ENCODERS
endif

ifeq ($(strip $(RGB_ENCODERS)), yes)
    ifeq ($(strip $(STAGGERED_LAYOUT)), yes)
        OPT_DEFS += -DSTAGGERED_RGB_ENCODERS=$(strip $(STAGGERED_RGB_ENCODERS))
    endif
endif
