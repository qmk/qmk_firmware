# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
# If your custom treadstone32 pcb, you can rewrite to yes.
RGBLIGHT_ENABLE = yes  # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS = yes        # LED animations

# Other selectable option
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    # OPT_DEFS += -DRGBLIGHT_ANIMATIONS
    OPT_DEFS += -DLED_ANIMATIONS
endif

ifeq ($(strip $(IOS_DEVICE_ENABLE)), yes)
    OPT_DEFS += -DIOS_DEVICE_ENABLE
endif
