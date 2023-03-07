NO_REPEAT				 = yes
VERBOSE					 = yes
KEYBOARD_SHARED_EP       = yes
MOUSEKEY_ENABLE			 = yes

#Debug options
CONSOLE_ENABLE			 = no
DEBUG_MATRIX_SCAN_RATE   = no
DEBUG_MATRIX			 = no
NO_PRINT				 = yes
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

SRC += sten.c
