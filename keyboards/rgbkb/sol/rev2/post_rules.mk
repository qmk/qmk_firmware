# As long as the users rules.mk has include $(KEYBOARD)/post_rules.mk this will be run after to properly setup any keyboard features and defines

ifeq ($(strip $(IOS_DEVICE_ENABLE)), yes)
    OPT_DEFS += -DIOS_DEVICE_ENABLE
else ifeq ($(strip $(RGBLIGHT_FULL_POWER)), yes)
    OPT_DEFS += -DRGBLIGHT_FULL_POWER
endif

ifeq ($(strip $(RGB_MATRIX_KEYPRESSES)), yes)
    OPT_DEFS += -DRGB_MATRIX_KEYPRESSES
endif

ifeq ($(strip $(RGB_MATRIX_FRAMEBUFFER)), yes)
    OPT_DEFS += -DRGB_MATRIX_FRAMEBUFFER_EFFECTS
endif

ifeq ($(strip $(LED_MIRRORED)), yes)
    OPT_DEFS += -DLED_MIRRORED
endif

ifeq ($(strip $(FULLHAND_ENABLE)), yes)
    OPT_DEFS += -DFULLHAND_ENABLE
endif

ifeq ($(strip $(EXTRA_ENCODERS_ENABLE)), yes)
    OPT_DEFS += -DEXTRA_ENCODERS_ENABLE
endif

ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
    ifeq ($(strip $(ENCODER_ENABLE)), yes)
        ifneq ($(strip $(RGB_MATRIX_ENABLE)), no)
            ifneq ($(strip $(RGB_OLED_MENU)), no)
                OPT_DEFS += -DRGB_OLED_MENU=$(strip $(RGB_OLED_MENU))
            endif
        endif
    endif
endif
