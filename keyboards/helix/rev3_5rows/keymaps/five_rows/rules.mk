USER_NAME := mtei

 CONSOLE_ENABLE = no        # Console for debug
 COMMAND_ENABLE = no        # Commands for debug and configuration
 # CONSOLE_ENABLE and COMMAND_ENABLE
 #      yes, no  +1500
 #      yes, yes +3200
 #      no,  yes +400
ENCODER_ENABLE = no
LTO_ENABLE = no  # if firmware size over limit, try this option
LED_ANIMATIONS = yes

CUSTOM_DELAY = yes

ifneq ($(strip $(HELIX)),)
  define KEYMAP_OPTION_PARSE
    # parse 'dispoff', 'consle', 'back', 'oled', 'no-ani', 'mini-ani', 'lto', 'no-lto', 'no-enc', 'scan', 'scan-api'
    $(if $(SHOW_PARCE),$(info parse .$1.))  #debug
    ifeq ($(strip $1),dispoff)
        OLED_ENABLE = no
        RGBLIGHT_ENABLE = no
    endif
    ifeq ($(strip $1),console)
        CONSOLE_ENABLE = yes
    endif
    ifeq ($(strip $1),debug)
        DEBUG_CONFIG = yes
    endif
    ifneq ($(filter nodebug no-debug no_debug,$(strip $1)),)
        DEBUG_CONFIG = no
    endif
    ifneq ($(filter enc,$(strip $1)),)
        ENCODER_ENABLE = yes
    endif
    ifneq ($(filter noenc no-enc no_enc,$(strip $1)),)
        ENCODER_ENABLE = no
    endif
    ifeq ($(strip $1),oled)
        OLED_ENABLE = yes
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
    ifeq ($(strip $1),scan-api)
        # use DEBUG_MATRIX_SCAN_RATE
        # see docs/newbs_testing_debugging.md
        DEBUG_MATRIX_SCAN_RATE_ENABLE = api
    endif
  endef # end of KEYMAP_OPTION_PARSE

  COMMA=,
  $(eval $(foreach A_OPTION_NAME,$(subst $(COMMA), ,$(HELIX)),  \
      $(call KEYMAP_OPTION_PARSE,$(A_OPTION_NAME))))
endif

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    OPT_DEFS += -DLED_ANIMATIONS
    OPT_DEFS += -DLED_ANIMATIONS_LEVEL=2
endif

ifeq ($(strip $(LED_ANIMATIONS)), mini)
    OPT_DEFS += -DLED_ANIMATIONS
    OPT_DEFS += -DLED_ANIMATIONS_LEVEL=1
endif

ifeq ($(strip $(CUSTOM_DELAY)),yes)
    SRC += matrix_output_unselect_delay.c
endif

ifeq ($(strip $(DEBUG_CONFIG)), yes)
    OPT_DEFS += -DDEBUG_CONFIG
endif
