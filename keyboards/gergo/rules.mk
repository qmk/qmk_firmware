#----------------------------------------------------------------------------
# make gergo:germ:dfu
# Make sure you have dfu-programmer installed!
#----------------------------------------------------------------------------

# Source includes
SRC += matrix.c i2c_master.c
#OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# Hardware info
MCU = atmega32u4
F_CPU = 16000000
ARCH = AVR8
BOOTLOADER = atmel-dfu
F_USB = $(F_CPU)
LAYOUTS = ergodox


# Firmware options
BALLER = yes # Enable to ball out
BALLSTEP = 20  			# Multiple in px to move, multiplied by layer number
SCROLLSTEP = 3 			# Lines to scroll with ball
MOUSEKEY_ENABLE  = yes  # Mouse keys(+4700), needed for baller
POINTING_DEVICE_ENABLE = yes

EXTRAKEY_ENABLE  = yes # Audio control and System control(+450)
CONSOLE_ENABLE   = yes # Console for debug(+400)
COMMAND_ENABLE   = yes # Commands for debug and configuration
CUSTOM_MATRIX    = yes # Custom matrix file for the ErgoDox EZ
NKRO_ENABLE      = no  # USB Nkey Rollover
UNICODE_ENABLE   = yes # Unicode

#Debug options
VERBOSE 		 = yes
DEBUG_MATRIX_SCAN_RATE = no
DEBUG_BALLER = no
DEBUG_MATRIX= no


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
    OPT_DEFS += -DBALLER
endif
ifeq ($(strip $(DEBUG_BALLER)), yes)
    OPT_DEFS += -DDEBUG_BALLER
endif
ifeq ($(strip $(DEBUG_MATRIX)), yes)
    OPT_DEFS += -DDEBUG_MATRIX
endif
