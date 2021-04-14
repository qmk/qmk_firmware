#----------------------------------------------------------------------------
# make gergo:germ:dfu
# Make sure you have dfu-programmer installed!
#----------------------------------------------------------------------------
# Firmware options
SRC += winternebs.c
MOUSEKEY_ENABLE 					= yes
COMBO_ENABLE = yes
VPATH += keyboards/gboards/

#Debug options
#VERBOSE 		 							= yes
#DEBUG_MATRIX_SCAN_RATE   	= no
#DEBUG_MATRIX		 					= yes
CONSOLE_ENABLE						= no

