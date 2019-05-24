# Overridden build options from rev1

# RGB Options
LED_MIRRORED            = no        # Mirror LEDs across halves (enable DIP 1 on slave, and DIP 2 and 3 on master)

# Misc
OLED_DRIVER_ENABLE      = yes       # Enable the OLED Driver





# Do not edit past here

ifeq ($(strip $(IOS_DEVICE_ENABLE)), yes)
    OPT_DEFS += -DIOS_DEVICE_ENABLE
else ifeq ($(strip $(RGBLIGHT_FULL_POWER)), yes)
    OPT_DEFS += -DRGBLIGHT_FULL_POWER
endif

ifeq ($(strip $(RGB_MATRIX_KEYPRESSES)), yes)
    OPT_DEFS += -DRGB_MATRIX_KEYPRESSES
endif

ifeq ($(strip $(RGB_MATRIX_FRAMEBUFFER)), yes)
    OPT_DEFS += -RGB_MATRIX_FRAMEBUFFER_EFFECTS
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

