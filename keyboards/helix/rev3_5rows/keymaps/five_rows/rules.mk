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

ifneq ($(strip $(HELIX)),)
  define KEYMAP_OPTION_PARSE
    # $xinfo .$1.x #debug
    # parse  'dispoff', 'consle', 'back', 'oled'
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
    ifeq ($(strip $1),scan)
        # use DEBUG_MATRIX_SCAN_RATE
        # see docs/newbs_testing_debugging.md
        OPT_DEFS +=  -DDEBUG_MATRIX_SCAN_RATE
        CONSOLE_ENABLE = yes
        SRC += keyboard_post_init_user_scan.c
    endif
  endef # end of KEYMAP_OPTION_PARSE

  COMMA=,
  $(eval $(foreach A_OPTION_NAME,$(subst $(COMMA), ,$(HELIX)),  \
      $(call KEYMAP_OPTION_PARSE,$(A_OPTION_NAME))))
endif
