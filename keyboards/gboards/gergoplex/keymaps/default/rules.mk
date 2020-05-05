#----------------------------------------------------------------------------
# make gergo:germ:dfu
# Make sure you have dfu-programmer installed!
#----------------------------------------------------------------------------
# Firmware options
MOUSEKEY_ENABLE 					= no

#Debug options
VERBOSE 		 							= yes
DEBUG_MATRIX_SCAN_RATE   	= no
DEBUG_MATRIX		 					= yes
CONSOLE_ENABLE						= yes

#Combos!
VPATH               			+=  keyboards/gboards/

# A bunch of stuff that you shouldn't touch unless you
# know what you're doing.
#
# No touchy, capiche?
SRC += matrix.c i2c_master.c
ifeq ($(strip $(DEBUG_MATRIX)), yes)
    OPT_DEFS += -DDEBUG_MATRIX
endif
