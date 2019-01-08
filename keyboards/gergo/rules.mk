#----------------------------------------------------------------------------
# make gergo:germ:dfu
# Make sure you have dfu-programmer installed!
# This is the keyboard level makefile, override these settings 
# in your layouts rules.mk!
#---------------------------------------------------------------------------
BOOTLOADER = atmel-dfu
F_USB = $(F_CPU)


# Firmware options
BALLER = yes # Enable to ball out
BALLSTEP = 20  			# Multiple in px to move, multiplied by layer number
SCROLLSTEP = 1 			# Lines to scroll with ball
MOUSEKEY_ENABLE  = yes  # Mouse keys(+4700), needed for baller
POINTING_DEVICE_ENABLE = yes

EXTRAKEY_ENABLE  = yes # Audio control and System control(+450)
CONSOLE_ENABLE   = yes # Console for debug(+400)
COMMAND_ENABLE   = yes # Commands for debug and configuration
NKRO_ENABLE      = no  # USB Nkey Rollover
UNICODE_ENABLE   = yes # Unicode

#Debug options
VERBOSE 		 = yes
DEBUG_MATRIX_SCAN_RATE = no
DEBUG_BALLER = no
DEBUG_MATRIX= no
