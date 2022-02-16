#
#  post_rules.mk contains post-processing rules for the Helix keyboard.
#
#   Post-processing rules convert keyboard-specific shortcuts (that represent
#   combinations of standard options) into QMK standard options.
#

-include $(strip $(HELIX_TOP_DIR)/pico/override_helix_options.mk) ## File dedicated to maintenance

  ifneq ($(strip $(HELIX)),)
    COMMA=,
    helix_option := $(subst $(COMMA), , $(HELIX))
    ifneq ($(filter no-ani,$(helix_option)),)
      LED_ANIMATIONS = no
    endif
    ifneq ($(filter ios,$(helix_option)),)
      IOS_DEVICE_ENABLE = yes
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
  $(info Helix Spacific Build Options)
  $(info -  OLED_ENABLE          = $(OLED_ENABLE))
  $(info -  LED_BACK_ENABLE      = $(LED_BACK_ENABLE))
  $(info -  LED_UNDERGLOW_ENABLE = $(LED_UNDERGLOW_ENABLE))
  $(info -  LED_ANIMATIONS       = $(LED_ANIMATIONS))
  $(info -  IOS_DEVICE_ENABLE    = $(IOS_DEVICE_ENABLE))
  $(info )
  $(info QMK Build Options)
  $(info -- SPLIT_KEYBOARD     = $(SPLIT_KEYBOARD))
  $(info -- AUDIO_ENABLE       = $(AUDIO_ENABLE))
  $(info -- RGBLIGHT_ENABLE    = $(RGBLIGHT_ENABLE))
  $(info -- CONSOLE_ENABLE     = $(CONSOLE_ENABLE))
  $(info -- OPT_DEFS           = $(OPT_DEFS))
  $(info -- LTO_ENABLE         = $(LTO_ENABLE))
  $(info )
endif

OLED_ENABLE = no # disable OLED in TOP/common_features.mk
