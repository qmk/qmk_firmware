# QMK Standard Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
#   See TOP/docs/config_options.md for more information.
#
 CONSOLE_ENABLE = no        # Console for debug
 COMMAND_ENABLE = no        # Commands for debug and configuration
 # CONSOLE_ENABLE and COMMAND_ENABLE
 #      yes, no  +1500
 #      yes, yes +3200
 #      no,  yes +400
LTO_ENABLE = no  # if firmware size over limit, try this option
LED_ANIMATIONS = yes

ifneq ($(strip $(HELIX)),)
  define KEYMAP_OPTION_PARSE
    # parse 'dispoff', 'consle', 'back', 'oled', 'no-ani', 'mini-ani', 'lto', 'no-lto', 'scan'
    $(if $(SHOW_PARCE),$(info parse .$1.))  #debug
    ifeq ($(strip $1),dispoff)
        OLED_DRIVER_ENABLE = no
        RGBLIGHT_ENABLE = no
    endif
    ifeq ($(strip $1),console)
        CONSOLE_ENABLE = yes
    endif
    ifeq ($(strip $1),oled)
        OLED_DRIVER_ENABLE = yes
    endif
    ifeq ($(strip $1),back)
        RGBLIGHT_ENABLE = yes
    endif
    ifneq ($(filter na no_ani no-ani,$(strip $1)),)
        LED_ANIMATIONS = no
    endif
    ifneq ($(filter mini-ani mini_ani,$(strip $1)),)
        LED_ANIMATIONS = mini
    endif
    ifneq ($(filter ani animation,$(strip $1)),)
        LED_ANIMATIONS = yes
    endif
    ifeq ($(strip $1),lto)
        LTO_ENABLE = yes
    endif
    ifneq ($(filter nolto no-lto no_lto,$(strip $1)),)
        LTO_ENABLE = no
    endif
    ifeq ($(strip $1),scan)
        # use DEBUG_MATRIX_SCAN_RATE
        # see docs/newbs_testing_debugging.md
        DEBUG_MATRIX_SCAN_RATE_ENABLE = yes
    endif
  endef # end of KEYMAP_OPTION_PARSE

  COMMA=,
  $(eval $(foreach A_OPTION_NAME,$(subst $(COMMA), ,$(HELIX)),  \
      $(call KEYMAP_OPTION_PARSE,$(A_OPTION_NAME))))
endif

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    OPT_DEFS += -DLED_ANIMATIONS=2
endif

ifeq ($(strip $(LED_ANIMATIONS)), mini)
    OPT_DEFS += -DLED_ANIMATIONS=1
endif
