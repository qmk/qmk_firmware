##############################################################################
# Build global options
# NOTE: Can be overridden externally.
#

# Compiler options here.
ifeq ($(USE_OPT),)
  USE_OPT = -O2 -ggdb -fomit-frame-pointer -falign-functions=16 -std=gnu99 -DPROTOCOL_CHIBIOS
endif

# C specific options here (added to USE_OPT).
ifeq ($(USE_COPT),)
  USE_COPT =
endif

# include specific config.h?
ifdef CONFIG_H
    USE_COPT += -include $(CONFIG_H)
endif

# C++ specific options here (added to USE_OPT).
ifeq ($(USE_CPPOPT),)
  USE_CPPOPT = -fno-rtti
endif

# Enable this if you want the linker to remove unused code and data
ifeq ($(USE_LINK_GC),)
  USE_LINK_GC = yes
endif

# Linker extra options here.
ifeq ($(USE_LDOPT),)
  USE_LDOPT =
endif

# Enable this if you want link time optimizations (LTO)
ifeq ($(USE_LTO),)
  USE_LTO = no
endif

# If enabled, this option allows to compile the application in THUMB mode.
ifeq ($(USE_THUMB),)
  USE_THUMB = yes
endif

# Enable this if you want to see the full log while compiling.
ifeq ($(USE_VERBOSE_COMPILE),)
  USE_VERBOSE_COMPILE = no
endif

# If enabled, this option makes the build process faster by not compiling
# modules not used in the current configuration.
ifeq ($(USE_SMART_BUILD),)
  USE_SMART_BUILD = yes
endif

#
# Build global options
##############################################################################

##############################################################################
# Architecture or project specific options
#

# Stack size to be allocated to the Cortex-M process stack. This stack is
# the stack used by the main() thread.
ifeq ($(USE_PROCESS_STACKSIZE),)
  USE_PROCESS_STACKSIZE = 0x200
endif

# Stack size to the allocated to the Cortex-M main/exceptions stack. This
# stack is used for processing interrupts and exceptions.
ifeq ($(USE_EXCEPTIONS_STACKSIZE),)
  USE_EXCEPTIONS_STACKSIZE = 0x400
endif

#
# Architecture or project specific options
##############################################################################

##############################################################################
# Project, sources and paths
#

# Imported source files and paths
CHIBIOS ?= $(TMK_PATH)/../lib/chibios
CHIBIOS_CONTRIB ?= $(TMK_PATH)/../lib/chibios-contrib
# Startup files. Try a few different locations, for compability with old versions and 
# for things hardware in the contrib repository
STARTUP_MK = $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/startup_$(MCU_STARTUP).mk
ifeq ("$(wildcard $(STARTUP_MK))","")
	STARTUP_MK = $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_$(MCU_STARTUP).mk
	ifeq ("$(wildcard $(STARTUP_MK))","")
		STARTUP_MK = $(CHIBIOS_CONTRIB)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_$(MCU_STARTUP).mk
	endif
endif
include $(STARTUP_MK)
# HAL-OSAL files (optional).
include $(CHIBIOS)/os/hal/hal.mk

PLATFORM_MK = $(CHIBIOS)/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)/platform.mk
ifeq ("$(wildcard $(PLATFORM_MK))","")
PLATFORM_MK = $(CHIBIOS_CONTRIB)/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)/platform.mk
endif
include $(PLATFORM_MK)


BOARD_MK = $(KEYBOARD_PATH)/boards/$(BOARD)/board.mk
ifeq ("$(wildcard $(BOARD_MK))","")
	BOARD_MK = $(CHIBIOS)/os/hal/boards/$(BOARD)/board.mk
	ifeq ("$(wildcard $(BOARD_MK))","")
		BOARD_MK = $(CHIBIOS_CONTRIB)/os/hal/boards/$(BOARD)/board.mk
	endif
endif
include $(BOARD_MK)
include $(CHIBIOS)/os/hal/osal/rt/osal.mk
# RTOS files (optional).
include $(CHIBIOS)/os/rt/rt.mk
# Compability with old version
PORT_V = $(CHIBIOS)/os/rt/ports/ARMCMx/compilers/GCC/mk/port_v$(ARMV)m.mk
ifeq ("$(wildcard $(PORT_V))","")
PORT_V = $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/port_v$(ARMV)m.mk
endif
include $(PORT_V)
# Other files (optional).
include $(CHIBIOS)/os/hal/lib/streams/streams.mk

# Define linker script file here
ifneq ("$(wildcard $(KEYBOARD_PATH)/ld/$(MCU_LDSCRIPT).ld)","")
LDSCRIPT = $(KEYBOARD_PATH)/ld/$(MCU_LDSCRIPT).ld
else
LDSCRIPT = $(STARTUPLD)/$(MCU_LDSCRIPT).ld
endif

# C sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CSRC = $(STARTUPSRC) \
       $(KERNSRC) \
       $(PORTSRC) \
       $(OSALSRC) \
       $(HALSRC) \
       $(PLATFORMSRC) \
       $(BOARDSRC) \
       $(STREAMSSRC) \
       $(SRC)

# C++ sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CPPSRC =

# C sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACSRC =

# C++ sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACPPSRC =

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCSRC =

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCPPSRC =

# List ASM source files here
ASMSRC =
ASMXSRC = $(STARTUPASM) $(PORTASM) $(OSALASM)

INCDIR = $(CHIBIOS)/os/license \
         $(STARTUPINC) $(KERNINC) $(PORTINC) $(OSALINC) \
         $(HALINC) $(PLATFORMINC) $(BOARDINC) $(TESTINC) \
         $(STREAMSINC) $(CHIBIOS)/os/various 

#
# Project, sources and paths
##############################################################################


##############################################################################
# Compiler settings
#

#TRGT = arm-elf-
TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CPPC = $(TRGT)g++
# Enable loading with g++ only if you need C++ runtime support.
# NOTE: You can use C++ even without C++ support if you are careful. C++
#       runtime support makes code size explode.
LD   = $(TRGT)gcc
#LD   = $(TRGT)g++
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
AR   = $(TRGT)ar
OD   = $(TRGT)objdump
SZ   = $(TRGT)size -A
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary

# ARM-specific options here
AOPT =

# THUMB-specific options here
TOPT = -mthumb -DTHUMB

# Define C warning options here
CWARN = -Wall -Wstrict-prototypes -Wno-missing-field-initializers -Werror
#CWARN = -Wall -Wextra -Wundef -Wstrict-prototypes -Wno-missing-field-initializers -Werror

# Define C++ warning options here
CPPWARN = -Wall -Wextra -Wundef

#
# Compiler settings
##############################################################################

##############################################################################
# Start of user section
#

# List all user C define here, like -D_DEBUG=1
## Select which interfaces to include here!
UDEFS += $(OPT_DEFS)

# Define ASM defines here
UADEFS += $(OPT_DEFS)
# bootloader definitions may be used in the startup .s file
ifneq ("$(wildcard $(KEYBOARD_PATH)/bootloader_defs.h)","")
    UADEFS += -include $(KEYBOARD_PATH)/bootloader_defs.h
    UDEFS += -include $(KEYBOARD_PATH)/bootloader_defs.h
else ifneq ("$(wildcard $(KEYBOARD_PATH)/boards/$(BOARD)/bootloader_defs.h)","")
    UADEFS += -include $(KEYBOARD_PATH)/boards/$(BOARD)/bootloader_defs.h
    UDEFS += -include $(KEYBOARD_PATH)/boards/$(BOARD)/bootloader_defs.h
endif

# List all user directories here
UINCDIR = $(VPATH)

# List the user directory to look for the libraries here
#ULIBDIR =

# List all user libraries here
#ULIBS =

#
# End of user defines
##############################################################################

OLDVPATH:=$(VPATH)

RULESPATH = $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC
ifeq ("$(wildcard $(RULESPATH)/rules.mk)","")
RULESPATH = $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC
endif
include $(RULESPATH)/rules.mk

# We need to fix the VPATH, since the ChibiOS rules assume that all sources 
# have absolute paths, creates a new VPATH path based on that
VPATH:=$(VPATH) $(OLDVPATH)