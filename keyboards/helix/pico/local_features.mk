#
#  local_features.mk contains post-processing rules for the Helix keyboard.
#
#   Post-processing rules convert keyboard-specific shortcuts (that represent
#   combinations of standard options) into QMK standard options.
#

define HELIX_CUSTOMISE_MSG
  $(info Helix Spacific Build Options)
  $(info -  OLED_ENABLE          = $(OLED_ENABLE))
  $(info -  LED_BACK_ENABLE      = $(LED_BACK_ENABLE))
  $(info -  LED_UNDERGLOW_ENABLE = $(LED_UNDERGLOW_ENABLE))
  $(info -  LED_ANIMATION        = $(LED_ANIMATIONS))
  $(info -  IOS_DEVICE_ENABLE    = $(IOS_DEVICE_ENABLE))
  $(info )
endef

  ifneq ($(strip $(HELIX)),)
    ### Helix keyboard keymap: convenient command line option
    ##    make HELIX=<options> helix/pico:<keymap>
    ##    option= oled | back | under | no_ani | na | ios | verbose
    ##    ex.
    ##      make HELIX=oled          helix/pico:<keymap>
    ##      make HELIX=oled,back     helix/pico:<keymap>
    ##      make HELIX=oled,under    helix/pico:<keymap>
    ##      make HELIX=oled,back,na  helix/pico:<keymap>
    ##      make HELIX=oled,back,ios helix/pico:<keymap>
    ##
    ifeq ($(findstring oled,$(HELIX)), oled)
      OLED_ENABLE = yes
    endif
    ifeq ($(findstring back,$(HELIX)), back)
      LED_BACK_ENABLE = yes
    else ifeq ($(findstring under,$(HELIX)), under)
      LED_UNDERGLOW_ENABLE = yes
    endif
    ifeq ($(findstring na,$(HELIX)), na)
      LED_ANIMATIONS = no
    endif
    ifeq ($(findstring no_ani,$(HELIX)), no_ani)
      LED_ANIMATIONS = no
    endif
    ifeq ($(findstring ios,$(HELIX)), ios)
      IOS_DEVICE_ENABLE = yes
    endif
    ifeq ($(findstring verbose,$(HELIX)), verbose)
       SHOW_VERBOSE_INFO = yes
    endif
    SHOW_HELIX_OPTIONS = yes
  endif

########
# convert Helix-specific options (that represent combinations of standard options)
#   into QMK standard options.

ifeq ($(strip $(LED_BACK_ENABLE)), yes)
  RGBLIGHT_ENABLE = yes
  OPT_DEFS += -DRGBLED_BACK
  ifeq ($(strip $(LED_UNDERGLOW_ENABLE)), yes)
    $(eval $(call HELIX_CUSTOMISE_MSG))
    $(error LED_BACK_ENABLE and LED_UNDERGLOW_ENABLE both 'yes')
  endif
else ifeq ($(strip $(LED_UNDERGLOW_ENABLE)), yes)
  RGBLIGHT_ENABLE = yes
endif

ifeq ($(strip $(IOS_DEVICE_ENABLE)), yes)
    OPT_DEFS += -DIOS_DEVICE_ENABLE
endif

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    OPT_DEFS += -DLED_ANIMATIONS
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
    OPT_DEFS += -DOLED_ENABLE
endif

ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
    OPT_DEFS += -DLOCAL_GLCDFONT
endif

ifeq ($(strip $(AUDIO_ENABLE)),yes)
  ifeq ($(strip $(RGBLIGHT_ENABLE)),yes)
    LINK_TIME_OPTIMIZATION_ENABLE = yes
  endif
  ifeq ($(strip $(OLED_ENABLE)),yes)
    LINK_TIME_OPTIMIZATION_ENABLE = yes
  endif
endif

ifneq ($(strip $(SHOW_HELIX_OPTIONS)),)
  $(eval $(call HELIX_CUSTOMISE_MSG))
  ifneq ($(strip $(SHOW_VERBOSE_INFO)),)
     $(info -- RGBLIGHT_ENABLE = $(RGBLIGHT_ENABLE))
     $(info -- OPT_DEFS        = $(OPT_DEFS))
     $(info -- LINK_TIME_OPTIMIZATION_ENABLE = $(LINK_TIME_OPTIMIZATION_ENABLE))
     $(info )
  endif
endif
