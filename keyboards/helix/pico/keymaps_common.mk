### Helix Pico keyboard 'MAP_NAME' keymap: convenient command line option
##    make HELIX=<options> helix/pico:MAP_NAME
##    option= oled | back | under | na | ios
##    ex.
##      make HELIX=oled          helix/pico:MAP_NAME
##      make HELIX=oled,back     helix/pico:MAP_NAME
##      make HELIX=oled,under    helix/pico:MAP_NAME
##      make HELIX=oled,back,na  helix/pico:MAP_NAME
##      make HELIX=oled,back,ios helix/pico:MAP_NAME
##
ifneq ($(strip $(HELIX)),)
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
  ifeq ($(findstring ios,$(HELIX)), ios)
    IOS_DEVICE_ENABLE = yes
  endif
  $(eval $(call HELIX_CUSTOMISE_MSG))
  $(info )
endif

# Uncomment these for checking
#   jp: コンパイル時にカスタマイズの状態を表示したい時はコメントをはずします。
#   jp: 上記の HELIX= でコマンドライン上でカスタマイズを指定した場合は常にカスタマイズの状態を表示されます。
# $(eval $(call HELIX_CUSTOMISE_MSG))
# $(info )

ifeq ($(strip $(LED_BACK_ENABLE)), yes)
  RGBLIGHT_ENABLE = yes
  OPT_DEFS += -DRGBLED_BACK
  ifeq ($(strip $(LED_UNDERGLOW_ENABLE)), yes)
    $(eval $(call HELIX_CUSTOMISE_MSG))
    $(error LED_BACK_ENABLE and LED_UNDERGLOW_ENABLE both 'yes')
  endif
else ifeq ($(strip $(LED_UNDERGLOW_ENABLE)), yes)
  RGBLIGHT_ENABLE = yes
else
  RGBLIGHT_ENABLE = no
endif

ifeq ($(strip $(IOS_DEVICE_ENABLE)), yes)
    OPT_DEFS += -DIOS_DEVICE_ENABLE
endif

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    OPT_DEFS += -DRGBLIGHT_ANIMATIONS
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
    OPT_DEFS += -DOLED_ENABLE
endif

ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
    OPT_DEFS += -DLOCAL_GLCDFONT
endif

ifeq ($(strip $(AUDIO_ENABLE)),yes)
  ifeq ($(strip $(RGBLIGHT_ENABLE)),yes)
    Link_Time_Optimization = yes
  endif
  ifeq ($(strip $(OLED_ENABLE)),yes)
    Link_Time_Optimization = yes
  endif
endif

ifeq ($(strip $(Link_Time_Optimization)),yes)
    EXTRAFLAGS += -flto -DUSE_Link_Time_Optimization
endif
