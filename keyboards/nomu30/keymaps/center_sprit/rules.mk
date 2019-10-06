
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
MOUSEKEY_ENABLE =  yes       # Mouse keys
TAP_DANCE_ENABLE = yes

# If your custom treadstone32 pcb, you can rewrite to yes.
RGBLIGHT_ENABLE = yes  # LED underglow 
LED_ANIMATIONS = yes        # LED animations

# Other selectable option
IOS_DEVICE_ENABLE = no      # connect to IOS device 

ifeq 
    # OPT_DEFS += -DRGBLIGHT_ANIMATIONS
    OPT_DEFS += -DLED_ANIMATIONS
endif

ifeq 
    OPT_DEFS += -DIOS_DEVICE_ENABLE
endif

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend
