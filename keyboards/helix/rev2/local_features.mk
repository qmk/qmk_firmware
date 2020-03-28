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
  $(info -  LED_ANIMATIONS       = $(LED_ANIMATIONS))
  $(info -  IOS_DEVICE_ENABLE    = $(IOS_DEVICE_ENABLE))
  $(info )
endef

  ifneq ($(strip $(HELIX)),)
    ### Helix keyboard keymap: convenient command line option
    ##    make HELIX=<options> helix:<keymap>
    ##    option= oled | back | under | na | ios
    ##    ex.
    ##      make HELIX=oled          helix:<keymap>
    ##      make HELIX=oled,back     helix:<keymap>
    ##      make HELIX=oled,under    helix:<keymap>
    ##      make HELIX=oled,back,na  helix:<keymap>
    ##      make HELIX=oled,back,ios helix:<keymap>
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
    ifeq ($(findstring scan,$(HELIX)), scan)
      # use DEBUG_MATRIX_SCAN_RATE
      # see docs/newbs_testing_debugging.md
      OPT_DEFS +=  -DDEBUG_MATRIX_SCAN_RATE
      CONSOLE_ENABLE = yes
      SHOW_VERBOSE_INFO = yes
    endif
    ifeq ($(findstring verbose,$(HELIX)), verbose)
      SHOW_VERBOSE_INFO = yes
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
    SRC += local_drivers/i2c.c
    SRC += local_drivers/ssd1306.c
    KEYBOARD_PATHS += $(HELIX_TOP_DIR)/local_drivers
    OPT_DEFS += -DOLED_ENABLE
    ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
        OPT_DEFS += -DLOCAL_GLCDFONT
    endif
endif

ifneq ($(strip $(SHOW_HELIX_OPTIONS)),)
  $(eval $(call HELIX_CUSTOMISE_MSG))
  ifneq ($(strip $(SHOW_VERBOSE_INFO)),)
     $(info -- RGBLIGHT_ENABLE    = $(RGBLIGHT_ENABLE))
     $(info -- OLED_DRIVER_ENABLE = $(OLED_DRIVER_ENABLE))
     $(info -- CONSOLE_ENABLE     = $(CONSOLE_ENABLE))
     $(info -- OPT_DEFS           = $(OPT_DEFS))
     $(info -- LINK_TIME_OPTIMIZATION_ENABLE = $(LINK_TIME_OPTIMIZATION_ENABLE))
     $(info )
  endif
endif
