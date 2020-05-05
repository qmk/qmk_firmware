#----------------------------------------------------------------------------
# make georgi:default:dfu
# Make sure you have dfu-programmer installed!
#----------------------------------------------------------------------------

NO_REPEAT								 = no
VERBOSE									 = yes
KEYBOARD_SHARED_EP       = yes
CUSTOM_MATRIX						 = yes
COMBO_ENABLE						 = yes

#Firmware reduction options
MOUSEKEY_ENABLE					 = yes			# 1500 bytes
NO_TAPPING							 = no				# 2000 bytes
NO_PRINT								 = no

#Debug options
CONSOLE_ENABLE					 = yes
DEBUG_MATRIX_SCAN_RATE   = no
DEBUG_MATRIX						 = yes
ONLY_QWERTY							 = no

#Engine options
VPATH										+=  keyboards/gboards/
SRC                 		+=  g/engine.c config_engine.c

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
ifeq ($(strip $(ONLY_QWERTY)), yes)
    OPT_DEFS += -DONLYQWERTY
endif
ifeq ($(strip $(NO_TAPPING)), yes)
    OPT_DEFS += -DNO_ACTION_TAPPING
endif
