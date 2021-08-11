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

ifneq ($(strip $(MTEST)),)
  define KEYBOARD_OPTION_PARSE
    # parse 'consle', 'scan', 'no-scan', 'mdelay=?', 'mdelay0',
    #       'adaptive_delay', 'always_delay', 'matrix_debug_delay', 'matrix_debug_scan'
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
    ifeq ($(strip $1),common_delay)
        MATRIX_COMMON_DELAY = yes
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
    ifeq ($(strip $1),matrix_debug_delay)
        MATRIX_DEBUG_DELAY = yes
        MATRIX_DEBUG_SCAN = no
    endif
    ifeq ($(strip $1),matrix_debug_scan)
        MATRIX_DEBUG_DELAY = no
        MATRIX_DEBUG_SCAN = yes
    endif
  endef # end of KEYMAP_OPTION_PARSE

  COMMA=,
  $(eval $(foreach A_OPTION_NAME,$(subst $(COMMA), ,$(MTEST)),  \
      $(call KEYBOARD_OPTION_PARSE,$(A_OPTION_NAME))))
endif

ifneq ($(strip $(MDELAY)),)
    OPT_DEFS += -DMATRIX_IO_DELAY=$(strip $(MDELAY))
endif

ifeq ($(strip $(ADAPTIVE_DELAY)),yes)
    OPT_DEFS += -DMATRIX_IO_DELAY_ADAPTIVE
endif

ifeq ($(strip $(ADAPTIVE_DELAY2)),yes)
    OPT_DEFS += -DMATRIX_IO_DELAY_ADAPTIVE2
endif

ifeq ($(strip $(ADAPTIVE_DELAY_FAST)),yes)
    OPT_DEFS += -DMATRIX_IO_DELAY_ADAPTIVE_FAST
endif

ifeq ($(strip $(ALWAYS_DELAY)),yes)
    OPT_DEFS += -DMATRIX_IO_DELAY_ALWAYS
endif

ifeq ($(strip $(MATRIX_DEBUG_DELAY)),yes)
    OPT_DEFS += -DMATRIX_DEBUG_DELAY
    DEBUG_CONFIG = yes
endif

ifeq ($(strip $(MATRIX_DEBUG_SCAN)),yes)
    OPT_DEFS += -DMATRIX_DEBUG_SCAN
    DEBUG_CONFIG = yes
endif

ifeq ($(strip $(DEBUG_CONFIG)),yes)
    # include "debug_config.h" from {promicro|proton_c}/config.h
    OPT_DEFS += -DDEBUG_CONFIG
endif

ifeq ($(strip $(MATRIX_COMMON_DELAY)),yes)
    # use matrix_output_unselect_delay() in matrix_common.c
    OPT_DEFS += -DMATRIX_IO_DELAY_DEFAULT
endif

$(info -)
$(info -  DEBUG_MATRIX_SCAN_RATE_ENABLE = $(DEBUG_MATRIX_SCAN_RATE_ENABLE))
$(info -  CONSOLE_ENABLE      = $(CONSOLE_ENABLE))
$(info -  MDELAY              = $(MDELAY))
$(info -  MATRIX_COMMON_DELAY = $(MATRIX_COMMON_DELAY))
$(info -  OPT_DEFS            = $(OPT_DEFS))
