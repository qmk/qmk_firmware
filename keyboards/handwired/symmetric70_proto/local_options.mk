# Copyright (c) 2022 Takeshi Ishii (mtei@github)
# SPDX-License-Identifier: GPL-2.0-or-later

# matrix.c testing options
#  set MATRIX_IO_DELAY macro
#    make MTEST=mdelay0   symmetric70_proto/{promicro|proton_c}/{fast|normal}:default:flash
#    make MTEST=mdelay=1  symmetric70_proto/{promicro|proton_c}/{fast|normal}:default:flash
#    make MTEST=mdelay=10  symmetric70_proto/{promicro|proton_c}/{fast|normal}:default:flash
#  set DEBUG_MATRIX_SCAN_RATE_ENABLE yes
#    make MTEST=scan symmetric70_proto/{promicro|proton_c}/{fast|normal}:default:flash
#  set MATRIX_DEBUG_DELAY and MATRIX_IO_DELAY macro
#    make MTEST=matrix_debug_delay,mdelay0 symmetric70_proto/{promicro|proton_c}/{fast|normal}:default:flash
#  set MATRIX_DEBUG_SCAN
#    make MTEST=matrix_debug_scan symmetric70_proto/{promicro|proton_c}/{fast|normal}:default:flash
#  set MATRIX_DEBUG_DELAY and MATRIX_DEBUG_SCAN
#    make MTEST=matrix_debug_scan,matrix_debug_delay symmetric70_proto/{promicro|proton_c}/{fast|normal}:default:flash
#
# for users/mtei/matrix_read_cols_on_row.c
#   MTEST=mdelay_type=ipullup
#   MTEST=mdelay_type=time
#   MTEST=mdelay_type=adaptive
# for symmetric70_proto/{promicro|proton_c}/boost
#   CANCEL_BOOST=yes

ifneq ($(strip $(MTEST)),)
  define KEYBOARD_OPTION_PARSE
    # parse 'consle', 'scan', 'no-scan', 'mdelay=?', 'mdelay0',
    #       'adaptive_delay', 'always_delay', 'matrix_debug_delay', 'matrix_debug_scan'
    #       'matrix_opendrain'
    $(if $(SHOW_PARSE),$(info parse .$1.))  #for debug  'make SHOW_PARSE=y ...'
    ifeq ($(strip $1),console)
        CONSOLE_ENABLE = yes
    endif
    ifeq ($(strip $1),scan)
        DEBUG_MATRIX_SCAN_RATE_ENABLE = yes
    endif
    ifeq ($(strip $1),no-scan)
        DEBUG_MATRIX_SCAN_RATE_ENABLE = no
    endif
    ifneq ($(filter mdelay=%,$1),)
        MDELAY = $(patsubst mdelay=%,%,$1)
    endif
    ifeq ($(strip $1),mdelay0)
        MDELAY = 0
    endif
    ifeq ($(strip $1),adaptive_delay)
        ADAPTIVE_DELAY = yes
    endif
    ifeq ($(strip $1),adaptive_delay2)
        ADAPTIVE_DELAY2 = yes
    endif
    ifeq ($(strip $1),adaptive_delay_fast)
        ADAPTIVE_DELAY_FAST = yes
    endif
    ifeq ($(strip $1),always_delay)
        ALWAYS_DELAY = yes
    endif
    ifeq ($(filter mdelay_type=%,$1),mdelay_type=ipullup)
        CUSTOM_MATRIX_DELAY = input-pullup
    endif
    ifeq ($(filter mdelay_type=%,$1),mdelay_type=time)
        CUSTOM_MATRIX_DELAY = time
    endif
    ifeq ($(filter mdelay_type=%,$1),mdelay_type=adaptive)
        CUSTOM_MATRIX_DELAY = adaptive
    endif
    ifeq ($(filter mdelay_type=%,$1),mdelay_type=adaptive-time)
        CUSTOM_MATRIX_DELAY = adaptive-time
    endif
    ifeq ($(strip $1),matrix_debug_delay)
        MATRIX_DEBUG_DELAY = yes
    endif
    ifeq ($(strip $1),matrix_debug_scan)
        MATRIX_DEBUG_SCAN = yes
    endif
    ifeq ($(strip $1),matrix_opendrain)
        MATRIX_USE_OPENDRAIN_PULLUP = yes
    endif
  endef # end of KEYMAP_OPTION_PARSE

  COMMA=,
  $(eval $(foreach A_OPTION_NAME,$(subst $(COMMA), ,$(MTEST)),  \
      $(call KEYBOARD_OPTION_PARSE,$(A_OPTION_NAME))))
endif
