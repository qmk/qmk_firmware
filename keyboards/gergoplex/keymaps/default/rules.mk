#----------------------------------------------------------------------------
# make gergoplex:default:flash
# Make sure you have dfu-programmer installed!
#----------------------------------------------------------------------------
# Firmware options
MOUSEKEY_ENABLE = yes    	# Mouse keys, needed for baller

#Debug options
VERBOSE   	 							= yes
DEBUG_MATRIX_SCAN_RATE     = no
DEBUG_MATRIX  	 					= yes

# A bunch of stuff that you shouldn't touch unless you
# know what you're doing.
#
# No touchy, capiche?
ifeq ($(strip $(DEBUG_MATRIX)), yes)
    OPT_DEFS += -DDEBUG_MATRIX
endif
