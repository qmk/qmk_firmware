RGBLIGHT_ENABLE = yes

# If your custom naked60 pcb, you can rewrite to yes.
LED_ANIMATIONS = yes        # LED animations

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    # OPT_DEFS += -DRGBLIGHT_ANIMATIONS
    OPT_DEFS += -DLED_ANIMATIONS
endif

