#----------------------------------------------------------------------------
# make gergo:germ:dfu
# Make sure you have dfu-programmer installed!
#----------------------------------------------------------------------------
# Firmware options
BALLER = no 			# Enable to ball out
BALLSTEP = 20  			# Multiple in px to move, multiplied by layer number
SCROLLSTEP = 1 			# Lines to scroll with ball
MOUSEKEY_ENABLE = yes  		# Mouse keys, needed for baller
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
LOCAL_GLCDFONT = yes

#Debug options
VERBOSE 		 = yes
DEBUG_MATRIX_SCAN_RATE   = no
DEBUG_BALLER 		 = no
DEBUG_MATRIX		 = yes

# A bunch of stuff that you shouldn't touch unless you
# know what you're doing.
#
# No touchy, capiche?
ifneq ($(strip $(BALLSTEP)),)
    OPT_DEFS += -DTRKSTEP=$(strip $(BALLSTEP))
endif
ifneq ($(strip $(SCROLLSTEP)),)
    OPT_DEFS += -DSCROLLSTEP=$(strip $(SCROLLSTEP))
endif
ifeq ($(strip $(BALLER)), yes)
	POINTING_DEVICE_ENABLE	= yes
    OPT_DEFS += -DBALLER
endif
ifeq ($(strip $(DEBUG_BALLER)), yes)
    OPT_DEFS += -DDEBUG_BALLER
endif
ifeq ($(strip $(DEBUG_MATRIX)), yes)
    OPT_DEFS += -DDEBUG_MATRIX
endif
