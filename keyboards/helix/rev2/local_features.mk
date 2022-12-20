#
#  local_features.mk contains post-processing rules for the Helix keyboard.
#
#   Post-processing rules convert keyboard-specific shortcuts (that represent
#   combinations of standard options) into QMK standard options.
#

KEYBOARD_LOCAL_FEATURES_MK :=
-include $(strip $(HELIX_TOP_DIR)/rev2/override_helix_options.mk) ## File dedicated to maintenance

# Parse 'HELIX=xx,yy,zz' option
ifneq ($(strip $(HELIX)),)
    # make HELIX=ios helix/pico:AKEYMAP
    # make HELIX=no-ani helix/pico:AKEYMAP
    # make HELIX=no-oled helix/pico:AKEYMAP
    # make HELIX=ios,no-ani,no-oled helix/pico:AKEYMAP
    define HELIX_OPTION_PARSE
        # parce 'no-ani' 'ios' 'no-oled'
        $(if $(SHOW_PARCE),$(info parse .$1.))  #debug
        $(if $(HELIX_OVERRIDE_PARSE),$(call HELIX_OVERRIDE_PARSE,$1))

      ifeq ($(strip $1),ios)
        IOS_DEVICE_ENABLE = yes
      endif
      ifneq ($(filter na no_ani no-ani,$(strip $1)),)
        LED_ANIMATIONS = no
      endif
      ifneq ($(filter nooled no-oled,$(strip $1)),)
        OLED_ENABLE = no
      endif
      ifeq ($(strip $1),oled)
        OLED_ENABLE = yes
      endif
    endef # end of HELIX_OPTION_PARSE

    COMMA=,
    $(eval $(foreach A_OPTION_NAME,$(subst $(COMMA), ,$(HELIX)),  \
        $(call HELIX_OPTION_PARSE,$(A_OPTION_NAME))))

    SHOW_HELIX_OPTIONS = yes
endif

########
# convert Helix-specific options (that represent combinations of standard options)
#   into QMK standard options.

ifneq ($(strip $(HELIX_ROWS)), 4)
  ifneq ($(strip $(HELIX_ROWS)), 5)
    $(error HELIX_ROWS = $(strip $(HELIX_ROWS)) is unexpected value)
  endif
endif
OPT_DEFS += -DHELIX_ROWS=$(strip $(HELIX_ROWS))

ifeq ($(strip $(LED_BACK_ENABLE)), yes)
  RGBLIGHT_ENABLE = yes
  OPT_DEFS += -DRGBLED_BACK
  ifeq ($(strip $(LED_UNDERGLOW_ENABLE)), yes)
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
    OLED_DRIVER = SSD1306
    ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
       OPT_DEFS += -DOLED_FONT_H=\<helixfont.h\>
    else
       OPT_DEFS += -DOLED_FONT_H=\"common/glcdfont.c\"
    endif
endif

ifneq ($(strip $(SHOW_HELIX_OPTIONS)),)
  $(info Helix Spacific Build Options)
  $(info -  OLED_ENABLE          = $(OLED_ENABLE))
  $(info -  LED_BACK_ENABLE      = $(LED_BACK_ENABLE))
  $(info -  LED_UNDERGLOW_ENABLE = $(LED_UNDERGLOW_ENABLE))
  $(info -  LED_ANIMATIONS       = $(LED_ANIMATIONS))
  $(info -  IOS_DEVICE_ENABLE    = $(IOS_DEVICE_ENABLE))
  $(info )
  $(info QMK Build Options)
  $(info -- SPLIT_KEYBOARD     = $(SPLIT_KEYBOARD))
  $(info -- RGBLIGHT_ENABLE    = $(RGBLIGHT_ENABLE))
  $(info -- OLED_DRIVER        = $(OLED_DRIVER))
  $(info -- OLED_LOCAL_ENABLE  = $(OLED_LOCAL_ENABLE))
  $(info -- CONSOLE_ENABLE     = $(CONSOLE_ENABLE))
  $(info -- OPT_DEFS           = $(OPT_DEFS))
  $(info -- LTO_ENABLE         = $(LTO_ENABLE))
  $(info )
endif
