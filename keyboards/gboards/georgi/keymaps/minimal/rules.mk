NO_REPEAT				 = no
VERBOSE					 = yes
KEYBOARD_SHARED_EP       = yes

#Firmware reduction options
MOUSEKEY_ENABLE			 = no 		# 1500 bytes
NO_TAPPING				 = yes		# 2000 bytes
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

SRC += sten.c
