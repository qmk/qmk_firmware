#----------------------------------------------------------------------------
# make gergo:germ:dfu
# Make sure you have dfu-programmer installed!
#----------------------------------------------------------------------------
# Firmware options
BALLER = no 			# Enable to ball out
BALLSTEP = 20  			# Multiple in px to move, multiplied by layer number
SCROLLSTEP = 1 			# Lines to scroll with ball
MOUSEKEY_ENABLE = yes  		# Mouse keys(+4700), needed for baller

#Debug options
VERBOSE 		 = yes
DEBUG_MATRIX_SCAN_RATE   = no
DEBUG_BALLER 		 = no
DEBUG_MATRIX		 = yes

# A bunch of stuff that you shouldn't touch unless you
# know what you're doing.
#
# No touchy, capiche?
ifeq ($(strip $(DEBUG_MATRIX)), yes)
    OPT_DEFS += -DDEBUG_MATRIX
endif
