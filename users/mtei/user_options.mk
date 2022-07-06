# Copyright (c) 2022 Takeshi Ishii (mtei@github)
# SPDX-License-Identifier: GPL-2.0-or-later

#
#  make USROPT=<option>,<option>,...  <KEYBOARD>:<KEYMAP>
#  options:
#    dispoff:     OLED, RGBLIGHT disable
#    oled:        OLED enable
#    no-oled:     OLED disable
#    rgblight:    RGBLIGHT enable
#    no-rgblight: RGBLIGHT disable
#    no_ani:      RGBLIGHT ANIMATIONS disable
#    mini-ani:    RGBLIGHT ANIMATIONS mini set
#    ani:         RGBLIGHT ANIMATIONS enable
#    scan:        DEBUG_MATRIX_SCAN_RATE enable
#    scan-api:    DEBUG_MATRIX_SCAN_RATE api enable
#    mdelay=<num> MATRIX_IO_DELAY set <num>
#    mdelay_type=<type> use custom matrix_output_unselect_delay()
#                 type=no,ondemand
#    enc:         ENCODER enable
#    no-enc:      ENCODER disable
#
ifneq ($(strip $(USROPT)),)
  define USER_OPTION_PARSE
    # parse 'debug', 'no-debug', 'dispoff', 'consle', 'scan', 'no-scan', 'scan-api',
    #   'mdelay=?', 'mdelay0', 'colemak', 'dvorak', 'eucalyn', 'lto', 'no-lto'
    $(if $(SHOW_PARSE),$(info parse .$1.))  #for debug  'make SHOW_PARSE=y ...'
    ifeq ($(strip $1),debug)
        DEBUG_CONFIG = yes
    endif
    ifneq ($(filter nodebug no-debug no_debug,$(strip $1)),)
        DEBUG_CONFIG = no
    endif
    ifeq ($(strip $1),dispoff)
        OLED_ENABLE = no
        RGBLIGHT_ENABLE = no
        LED_BACK_ENABLE = no
        LED_UNDERGLOW_ENABLE = no
    endif
    ifneq ($(filter rgblight,$(strip $1)),)
        RGBLIGHT_ENABLE = yes
        LED_BACK_ENABLE = yes
    endif
    ifneq ($(filter norgblight no-rgblight,$(strip $1)),)
        RGBLIGHT_ENABLE = no
        LED_BACK_ENABLE = no
        LED_UNDERGLOW_ENABLE = no
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
    ifneq ($(filter nooled no-oled,$(strip $1)),)
        OLED_ENABLE = no
    endif
    ifeq ($(strip $1),oled)
        OLED_ENABLE = yes
    endif
    ifeq ($(strip $1),console)
        CONSOLE_ENABLE = yes
    endif
    ifeq ($(strip $1),scan)
        # use DEBUG_MATRIX_SCAN_RATE
        # see docs/newbs_testing_debugging.md
        DEBUG_MATRIX_SCAN_RATE_ENABLE = yes
    endif
    ifeq ($(strip $1),no-scan)
        DEBUG_MATRIX_SCAN_RATE_ENABLE = no
    endif
    ifeq ($(strip $1),scan-api)
        # use DEBUG_MATRIX_SCAN_RATE
        # see docs/newbs_testing_debugging.md
        DEBUG_MATRIX_SCAN_RATE_ENABLE = api
    endif
    ifneq ($(filter stimer sync-timer,$(strip $1)),)
        SYNC_TIMER_ENABLE = yes
    endif
    ifneq ($(filter nostimer no-sync-timer,$(strip $1)),)
        SYNC_TIMER_ENABLE = no
    endif
    ifeq ($(filter mdelay_type=%,$1),mdelay_type=no)
        CUSTOM_MATRIX_DELAY = no
    endif
    ifeq ($(filter mdelay_type=%,$1),mdelay_type=demand)
        CUSTOM_MATRIX_DELAY = on-demand
    endif
    ifneq ($(filter mdelay=%,$1),)
        MDELAY = $(patsubst mdelay=%,%,$1)
    endif
    ifeq ($(strip $1),mdelay0)
        MDELAY = 0
    endif
    ifeq ($(strip $1),colemak)
         ENABLE_COLEMAK = yes
    endif
    ifeq ($(strip $1),dvorak)
         ENABLE_DVORAK = yes
    endif
    ifeq ($(strip $1),eucalyn)
         ENABLE_EUCALYN = yes
    endif
    ifeq ($(strip $1),lto)
        LTO_ENABLE = yes
    endif
    ifneq ($(filter nolto no-lto no_lto,$(strip $1)),)
        LTO_ENABLE = no
    endif
    ifneq ($(filter enc,$(strip $1)),)
        ENCODER_ENABLE = yes
    endif
    ifneq ($(filter noenc no-enc no_enc,$(strip $1)),)
        ENCODER_ENABLE = no
    endif
    ifneq ($(filter debugenc debug-enc debug_enc,$(strip $1)),)
        DEBUG_ENCODER = yes
    endif
  endef # end of USER_OPTION_PARSE

  COMMA=,
  $(eval $(foreach A_OPTION_NAME,$(subst $(COMMA), ,$(USROPT)),  \
      $(call USER_OPTION_PARSE,$(A_OPTION_NAME))))
endif
