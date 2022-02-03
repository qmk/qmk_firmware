#
#  post_rules.mk contains post-processing rules for the Helix keyboard.
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

define HELIX_HELP_MSG
  $(info Helix keyboard convenient command line option)
  $(info -    make HELIX=<options> helix/pico:<keymap>)
  $(info -    option= oled | back | under | na | no-ani)
  $(info -             ios | sc | split-common | scan | verbose)
  $(info -    ex.)
  $(info -      make HELIX=oled     helix/pico:<keymap>)
  $(info -      make HELIX=back     helix/pico:<keymap>)
  $(info -      make HELIX=under    helix/pico:<keymap>)
  $(info -      make HELIX=back,na  helix/pico:<keymap>)
  $(info -      make HELIX=back,ios helix/pico:<keymap>)
  $(info )
endef

  ifneq ($(strip $(HELIX)),)
    COMMA=,
    helix_option := $(subst $(COMMA), , $(HELIX))
    ifneq ($(filter help,$(helix_option)),)
      $(eval $(call HELIX_HELP_MSG))
      $(error )
    endif
    ifneq ($(filter oled,$(helix_option)),)
      OLED_ENABLE = yes
    endif
    ifneq ($(filter back,$(helix_option)),)
      LED_BACK_ENABLE = yes
    else ifneq ($(filter under,$(helix_option)),)
      LED_UNDERGLOW_ENABLE = yes
    endif
    ifneq ($(filter na,$(helix_option)),)
      LED_ANIMATIONS = no
    endif
    ifneq ($(filter no_ani,$(helix_option)),)
      LED_ANIMATIONS = no
    endif
    ifneq ($(filter no-ani,$(helix_option)),)
      LED_ANIMATIONS = no
    endif
    ifneq ($(filter ios,$(helix_option)),)
      IOS_DEVICE_ENABLE = yes
    endif
    ifneq ($(filter sc,$(helix_option)),)
      SPLIT_KEYBOARD = yes
    endif
    ifneq ($(filter split-common,$(helix_option)),)
      SPLIT_KEYBOARD = yes
    endif
    ifneq ($(filter scan,$(helix_option)),)
      # use DEBUG_MATRIX_SCAN_RATE
      # see docs/newbs_testing_debugging.md
      OPT_DEFS +=  -DDEBUG_MATRIX_SCAN_RATE
      CONSOLE_ENABLE = yes
      SHOW_VERBOSE_INFO = yes
    endif
    ifneq ($(filter verbose,$(helix_option)),)
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

  SRC += pico/matrix.c
  SRC += pico/split_util.c
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
    SRC += local_drivers/i2c.c
    SRC += local_drivers/ssd1306.c
    KEYBOARD_PATHS += $(HELIX_TOP_DIR)/local_drivers
    OPT_DEFS += -DOLED_ENABLE
    ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
        OPT_DEFS += -DLOCAL_GLCDFONT
    endif
endif

ifeq ($(strip $(AUDIO_ENABLE)),yes)
  ifeq ($(strip $(RGBLIGHT_ENABLE)),yes)
    LTO_ENABLE = yes
  endif
  ifeq ($(strip $(OLED_ENABLE)),yes)
    LTO_ENABLE = yes
  endif
endif

ifneq ($(strip $(SHOW_HELIX_OPTIONS)),)
  $(eval $(call HELIX_CUSTOMISE_MSG))
  ifneq ($(strip $(SHOW_VERBOSE_INFO)),)
     $(info -- RGBLIGHT_ENABLE    = $(RGBLIGHT_ENABLE))
     $(info -- CONSOLE_ENABLE     = $(CONSOLE_ENABLE))
     $(info -- OPT_DEFS           = $(OPT_DEFS))
     $(info -- SPLIT_KEYBOARD     = $(SPLIT_KEYBOARD))
     $(info -- LTO_ENABLE         = $(LTO_ENABLE))
     $(info )
  endif
endif

OLED_ENABLE = no # disable OLED in TOP/common_features.mk
