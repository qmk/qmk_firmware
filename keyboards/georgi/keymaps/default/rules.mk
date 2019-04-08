#----------------------------------------------------------------------------
# make georgi:default:dfu
# Make sure you have dfu-programmer installed!
#----------------------------------------------------------------------------

NO_REPEAT				 = no
VERBOSE					 = yes
KEYBOARD_SHARED_EP       = yes
CUSTOM_MATRIX			 = yes
MOUSEKEY_ENABLE			 = yes

#Debug options
CONSOLE_ENABLE			 = yes
DEBUG_MATRIX_SCAN_RATE   = no
DEBUG_MATRIX			 = no
NO_PRINT				 = no

# A bunch of stuff that you shouldn't touch unless you
# know what you're doing.
#
# No touchy, capiche?
SRC += matrix.c i2c_master.c
ifeq ($(strip $(DEBUG_MATRIX)), yes)
    OPT_DEFS += -DDEBUG_MATRIX
endif
ifeq ($(strip $(NO_REPEAT)), yes)
    OPT_DEFS += -DNO_REPEAT
endif
ifeq ($(strip $(NO_PRINT)), yes)
    OPT_DEFS += -DNO_PRINT -DNO_DEBUG
endif
