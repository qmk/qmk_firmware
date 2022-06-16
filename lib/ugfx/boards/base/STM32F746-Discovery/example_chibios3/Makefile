# Possible Targets:	all clean Debug cleanDebug Release cleanRelease

##############################################################################################
# Settings
#

# General settings
	# See $(GFXLIB)/tools/gmake_scripts/readme.txt for the list of variables
	OPT_OS					= chibios
	OPT_THUMB				= yes
	OPT_LINK_OPTIMIZE		= no
	OPT_CPU					= stm32m7

# uGFX settings
	# See $(GFXLIB)/tools/gmake_scripts/library_ugfx.mk for the list of variables
	GFXLIB					= ../ugfx2
	GFXBOARD				= STM32F746-Discovery
	GFXDEMO					= applications/combo
	#GFXDRIVERS				=
	GFXSINGLEMAKE			= no

# ChibiOS settings
ifeq ($(OPT_OS),chibios)
	# See $(GFXLIB)/tools/gmake_scripts/os_chibios_3.mk for the list of variables
	CHIBIOS					= ../ChibiOS16
	CHIBIOS_VERSION			= 16
	CHIBIOS_CPUCLASS		= ARMCMx
	CHIBIOS_PLATFORM		= STM32
	CHIBIOS_DEVICE_FAMILY	= STM32F7xx
	CHIBIOS_STARTUP			= startup_stm32f7xx
	CHIBIOS_PORT			= v7m
	CHIBIOS_LDSCRIPT		= STM32F746xG.ld
	CHIBIOS_BOARD			= ST_STM32F746G_DISCOVERY
	#CHIBIOS_PROCESS_STACKSIZE = 0x400
	#CHIBIOS_EXCEPTIONS_STACKSIZE = 0x400
endif

# Raw32 settings
ifeq ($(OPT_OS),raw32)
	CMSIS			= ../STM32F7_Drivers/CMSIS
endif

#Special - Required for the drivers for this discovery board.
STMHAL		= ../STM32F7_Drivers/STM32F7xx_HAL_Driver


##############################################################################################
# Set these for your project
#

ARCH     = arm-none-eabi-
SRCFLAGS = -ggdb -O1
CFLAGS   = 
CXXFLAGS = -fno-rtti
ASFLAGS  =
LDFLAGS  =

SRC      = 

OBJS     =
DEFS     =
#DEFS     = GFX_OS_HEAP_SIZE=40960
LIBS     =
INCPATH  = 

LIBPATH  =
LDSCRIPT = 

##############################################################################################
# These should be at the end
#

include $(GFXLIB)/tools/gmake_scripts/library_ugfx.mk
include $(GFXLIB)/tools/gmake_scripts/os_$(OPT_OS).mk
include $(GFXLIB)/tools/gmake_scripts/compiler_gcc.mk
# *** EOF ***
