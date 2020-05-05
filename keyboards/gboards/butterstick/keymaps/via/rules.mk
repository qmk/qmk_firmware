#----------------------------------------------------------------------------
# make gergo:germ:dfu
# Make sure you have dfu-programmer installed!
#----------------------------------------------------------------------------
# Firmware options
MOUSEKEY_ENABLE = yes  		# Mouse keys(+4700), needed for baller
VIA_ENABLE = yes

#Debug options
VERBOSE 		 = yes
DEBUG_MATRIX_SCAN_RATE   = no
DEBUG_BALLER 		 = no
DEBUG_MATRIX		 = yes

ifeq ($(strip $(DEBUG_MATRIX)), yes)
    OPT_DEFS += -DDEBUG_MATRIX
endif
