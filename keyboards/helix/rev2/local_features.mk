#
#  local_features.mk contains post-processing rules for the Helix keyboard.
#
#   Post-processing rules convert keyboard-specific shortcuts (that represent
#   combinations of standard options) into QMK standard options.
#

KEYBOARD_LOCAL_FEATURES_MK :=

define HELIX_CUSTOMISE_MSG
  $(info Helix Spacific Build Options)
  $(info -  OLED_ENABLE          = $(OLED_ENABLE))
  $(info -  OLED_SELECT          = $(OLED_SELECT))
  $(info -  LED_BACK_ENABLE      = $(LED_BACK_ENABLE))
  $(info -  LED_UNDERGLOW_ENABLE = $(LED_UNDERGLOW_ENABLE))
  $(info -  LED_ANIMATIONS       = $(LED_ANIMATIONS))
  $(info -  IOS_DEVICE_ENABLE    = $(IOS_DEVICE_ENABLE))
  $(info )
endef

define HELIX_HELP_MSG
  $(info Helix keyboard convenient command line option)
  $(info -    make HELIX=<options> helix:<keymap>)
  $(info -    option= oled | core-oled | local-oled | no-oled )
  $(info -            back | no-back   | under      | na   | no-ani )
  $(info -             ios | sc        | split-common | scan | verbose)
  $(info -    eg.)
  $(info -      make HELIX=no-oled       helix:<keymap>)
  $(info -      make HELIX=oled,no-back  helix:<keymap>)
  $(info -      make HELIX=oled,under    helix:<keymap>)
  $(info -      make HELIX=oled,back,na  helix:<keymap>)
  $(info -      make HELIX=oled,back,ios helix:<keymap>)
  $(info )
endef

  ifneq ($(strip $(HELIX)),)
    define HELIX_OPTION_PARSE
      # parce 'oled' 'back' 'under' 'ios' etc.
      $(if $(SHOW_PARCE),$(info parse .$1.))  #debug

      ifeq ($(strip $1),help)
        HELP=on
      endif
      ifneq ($(filter nooled no-oled,$(strip $1)),)
        OLED_ENABLE = no
      endif
      ifeq ($(strip $1),oled)
        OLED_ENABLE = yes
      endif
      ifneq ($(filter core-oled core_oled newoled new-oled olednew oled-new,$(strip $1)),)
        OLED_ENABLE = yes
        OLED_SELECT = core
      endif
      ifneq ($(filter local-oled local_oled oldoled old-oled oledold oled-old,$(strip $1)),)
        OLED_ENABLE = yes
        OLED_SELECT = local
      endif
      ifneq ($(filter noback no-back nounder no-under,$(strip $1)),)
        LED_BACK_ENABLE = no
        LED_UNDERGLOW_ENABLE = no
      endif
      ifeq ($(strip $1),back)
        LED_BACK_ENABLE = yes
        LED_UNDERGLOW_ENABLE = no
      endif
      ifeq ($(strip $1),under)
        LED_BACK_ENABLE = no
        LED_UNDERGLOW_ENABLE = yes
      endif
      ifneq ($(filter na no_ani no-ani,$(strip $1)),)
        LED_ANIMATIONS = no
      endif
      ifeq ($(strip $1),ios)
        IOS_DEVICE_ENABLE = yes
      endif
      ifneq ($(filter sc split-common split_common,$(strip $1)),)
        SPLIT_KEYBOARD = yes
      endif
      ifneq ($(filter nosc no-sc no-split-common no-split_common,$(strip $1)),)
        SPLIT_KEYBOARD = no
      endif
      ifeq ($(strip $1),scan)
        # use DEBUG_MATRIX_SCAN_RATE
        # see docs/newbs_testing_debugging.md
        OPT_DEFS +=  -DDEBUG_MATRIX_SCAN_RATE
        CONSOLE_ENABLE = yes
        SHOW_VERBOSE_INFO = yes
      endif
      ifeq ($(strip $1),verbose)
        SHOW_VERBOSE_INFO = yes
      endif
      ifeq ($(strip $1),lto)
        LTO_ENABLE = yes
      endif
      ifneq ($(filter nolto no-lto no_lto,$(strip $1)),)
        LTO_ENABLE = no
      endif
    endef # end of HELIX_OPTION_PARSE

    COMMA=,
    $(eval $(foreach A_OPTION_NAME,$(subst $(COMMA), ,$(HELIX)),  \
        $(call HELIX_OPTION_PARSE,$(A_OPTION_NAME))))

    ifeq ($(strip $(HELP)),on)
       $(eval $(call HELIX_HELP_MSG))
       $(error )
    endif
    SHOW_HELIX_OPTIONS = yes
  endif

ifneq ($(strip $(SPLIT_KEYBOARD)), yes)
  SRC += local_drivers/serial.c
  KEYBOARD_PATHS += $(HELIX_TOP_DIR)/local_drivers

  # A workaround until #7089 is merged.
  #   serial.c must not be compiled with the -lto option.
  #   The current LIB_SRC has a side effect with the -fno-lto option, so use it.
  LIB_SRC += local_drivers/serial.c

  CUSTOM_MATRIX = yes

  SRC += rev2/matrix.c
  SRC += rev2/split_util.c
  SRC += rev2/split_scomm.c
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
    ifeq ($(strip $(OLED_SELECT)),core)
        OLED_DRIVER_ENABLE = yes
        ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
           OPT_DEFS += -DOLED_FONT_H=\<helixfont.h\>
        else
           OPT_DEFS += -DOLED_FONT_H=\"common/glcdfont.c\"
        endif
    else
        SRC += local_drivers/i2c.c
        SRC += local_drivers/ssd1306.c
        KEYBOARD_PATHS += $(HELIX_TOP_DIR)/local_drivers
        OPT_DEFS += -DOLED_ENABLE
        ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
            OPT_DEFS += -DLOCAL_GLCDFONT
        endif
    endif
endif

ifneq ($(strip $(SHOW_HELIX_OPTIONS)),)
  $(eval $(call HELIX_CUSTOMISE_MSG))
  ifneq ($(strip $(SHOW_VERBOSE_INFO)),)
     $(info -- RGBLIGHT_ENABLE    = $(RGBLIGHT_ENABLE))
     $(info -- OLED_DRIVER_ENABLE = $(OLED_DRIVER_ENABLE))
     $(info -- CONSOLE_ENABLE     = $(CONSOLE_ENABLE))
     $(info -- OPT_DEFS           = $(OPT_DEFS))
     $(info -- SPLIT_KEYBOARD     = $(SPLIT_KEYBOARD))
     $(info -- LTO_ENABLE         = $(LTO_ENABLE))
     $(info )
  endif
endif
