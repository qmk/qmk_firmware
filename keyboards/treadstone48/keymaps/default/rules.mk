TAP_DANCE_ENABLE = yes

# If your custom treadstone48 pcb, you can rewrite to yes.
OLED_ENABLE = no            # OLED_ENABLE
LED_UNDERGLOW_ENABLE = yes  # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS = yes        # LED animations

# Other selectable option
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
LOCAL_GLCDFONT = no         # use each keymaps "font.h" insted of "common/glcdfont.c"
# RHYMESTONE_RIGHTHAND = no   # If connect right hand side of the Rhymestone, set to yes.
ANGELINA_KEYMAP = no        # If Alfa verstion use set to yes.

ifeq ($(strip $(OLED_ENABLE)), yes)
    OPT_DEFS += -DOLED_ENABLE
endif

ifeq ($(strip $(LED_UNDERGLOW_ENABLE)), yes)
  RGBLIGHT_ENABLE = yes
else
  RGBLIGHT_ENABLE = no
endif

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    # OPT_DEFS += -DRGBLIGHT_ANIMATIONS
    OPT_DEFS += -DLED_ANIMATIONS
endif

ifeq ($(strip $(IOS_DEVICE_ENABLE)), yes)
    OPT_DEFS += -DIOS_DEVICE_ENABLE
endif

ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
    OPT_DEFS += -DLOCAL_GLCDFONT
endif

# ifeq ($(strip $(RHYMESTONE_RIGHTHAND)), yes)
#     OPT_DEFS += -DRHYMESTONE_RIGHTHAND
# endif

ifeq ($(strip $(ANGELINA_KEYMAP)), yes)
    OPT_DEFS += -DANGELINA_KEYMAP
endif

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

# If you want to change the display of OLED, you need to change here
SRC +=  ./common/oled_helper.c \
