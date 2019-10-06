#----------------------------------------------------------------------------
# make georgi:default:dfu
# Make sure you have dfu-programmer installed!
#----------------------------------------------------------------------------

NO_REPEAT				 = no
VERBOSE					 = yes
KEYBOARD_SHARED_EP       = yes
CUSTOM_MATRIX			 = yes

#Firmware reduction options
MOUSEKEY_ENABLE			 = yes 		# 1500 bytes
NO_TAPPING				 = no 	    # 2000 bytes
NO_PRINT				 = yes		

#Debug options
CONSOLE_ENABLE			 = no
DEBUG_MATRIX_SCAN_RATE   = no
DEBUG_MATRIX			 = no
ONLY_QWERTY				 = no

# A bunch of stuff that you shouldn't touch unless you
# know what you're doing.
#
# No touchy, capiche?
SRC += matrix.c i2c_master.c
ifeq 
    OPT_DEFS += -DDEBUG_MATRIX
endif
ifeq 
    OPT_DEFS += -DNO_REPEAT
endif
ifeq 
    OPT_DEFS += -DNO_PRINT -DNO_DEBUG
endif
ifeq 
    OPT_DEFS += -DONLYQWERTY
endif
ifeq 
    OPT_DEFS += -DNO_ACTION_TAPPING
endif
