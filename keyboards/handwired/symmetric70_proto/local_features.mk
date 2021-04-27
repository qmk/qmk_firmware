# matrix.c testing options
#  set MATRIX_IO_DELAY macro
#    make MTEST=mdelay0  symmetric70_proto/{promicro|proton_c}/{fast|normal}:default:flash
#    make MTEST=mdelay1  symmetric70_proto/{promicro|proton_c}/{fast|normal}:default:flash
#    make MTEST=mdelay10 symmetric70_proto/{promicro|proton_c}/{fast|normal}:default:flash
#    make MTEST=mdelay30 symmetric70_proto/{promicro|proton_c}/{fast|normal}:default:flash
#  set DEBUG_MATRIX_SCAN_RATE_ENABLE yes
#    make MTEST=scan symmetric70_proto/{promicro|proton_c}/{fast|normal}:default:flash
#  set MATRIX_DEBUG_DELAY and MATRIX_IO_DELAY macro
#    make MTEST=matrix_debug_delay,mdelay0 symmetric70_proto/{promicro|proton_c}/{fast|normal}:default:flash
#  set MATRIX_DEBUG_SCAN
#    make MTEST=matrix_debug_scan symmetric70_proto/{promicro|proton_c}/{fast|normal}:default:flash

ifneq ($(strip $(MTEST)),)
  define KEYBOARD_OPTION_PARSE
    # parse 'consle', 'scan', 'no-scan', 'mdelay0', ..., 'mdelay30',
    #       'adaptive_delay', 'allways_delay', 'matrix_debug_delay', 'matrix_debug_scan'
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
    ifeq ($(strip $1),mdelay0)
        MDELAY = 0
    endif
    ifeq ($(strip $1),mdelay1)
        MDELAY = 1
    endif
    ifeq ($(strip $1),mdelay2)
        MDELAY = 2
    endif
    ifeq ($(strip $1),mdelay3)
        MDELAY = 3
    endif
    ifeq ($(strip $1),mdelay4)
        MDELAY = 4
    endif
    ifeq ($(strip $1),mdelay5)
        MDELAY = 5
    endif
    ifeq ($(strip $1),mdelay10)
        MDELAY = 10
    endif
    ifeq ($(strip $1),mdelay20)
        MDELAY = 20
    endif
    ifeq ($(strip $1),mdelay30)
        MDELAY = 30
    endif
    ifeq ($(strip $1),common_delay)
        MATRIX_COMMON_DELAY = yes
    endif
    ifeq ($(strip $1),adaptive_delay)
	ADAPTIVE_DELAY = yes
    endif
    ifeq ($(strip $1),allways_delay)
        ALLWAYS_DELAY = yes
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

ifeq ($(strip $(ALLWAYS_DELAY)),yes)
    OPT_DEFS += -DMATRIX_IO_DELAY_ALLWAYS
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
