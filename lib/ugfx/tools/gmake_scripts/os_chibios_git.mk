#
# This file is subject to the terms of the GFX License. If a copy of
# the license was not distributed with this file, you can obtain one at:
#
#             http://ugfx.io/license.html
#

# See readme.txt for the make API

# Requirements:
#
# CHIBIOS                         The location of the ChibiOS code.    eg CHIBIOS = ../chibios
# CHIBIOS_CPUCLASS                The class of the CPU.    eg CHIBIOS_CPUCLASS = ARMCMx
# CHIBIOS_PLATFORM                The name of the ChibiOS platform.    eg CHIBIOS_PLATFORM = STM32
# CHIBIOS_DEVICE_FAMILY           The name of the ChibiOS device family.    eg CHIBIOS_DEVICE_FAMILY = STM32F4xx
# CHIBIOS_STARTUP                 The name of the ChibiOS startup files.    eg CHIBIOS_STARTUP = startup_stm32f4xx
# CHIBIOS_PORT                    The name of the ChibiOS port.    eg CHIBIOS_PORT = v7m
#

# Optional:
#
# CHIBIOS_LDSCRIPT                The name of the loader script    eg CHIBIOS_LDSCRIPT = STM32F429xI.ld
# CHIBIOS_BOARD                   The name of the ChibiOS board    eg CHIBIOS_BOARD = ST_STM32F429I_DISCOVERY - if not specified you must include equivalent code yourself
# CHIBIOS_VERSION                 Which version of ChibiOS is this (2 or 3) - default is 3
# CHIBIOS_PROCESS_STACKSIZE       Size of the ChibiOS process stack. Only useful if the link script supports it - default is 0x400
# CHIBIOS_EXCEPTIONS_STACKSIZE    Size of the ChibiOS exceptopms stack. Only useful if the link script supports it - default is 0x400
#
# Other ChibiOS things you might want to add to your SRC in your makefile...
#	$(TESTSRC) $(LWSRC) $(FATFSSRC) $(STREAMSSRC) $(SHELLSRC) $(CHIBIOS)/os/various/xxxx
#
# Other ChibiOS things you might want to add to your INCPATH in your makefile...
#	$(TESTINC) $(LWINC) $(FATFSINC) $(STREAMSINC) $(SHELLINC) $(CHIBIOS)/os/various
#
# Note we don't add the above source or folders to the project by default to avoid name potential name conflicts

PATHLIST += CHIBIOS

# Startup files.
include $(CHIBIOS)/os/common/startup/$(CHIBIOS_CPUCLASS)/compilers/GCC/mk/$(CHIBIOS_STARTUP).mk

# HAL-OSAL files (optional).
include $(CHIBIOS)/os/hal/hal.mk
include $(CHIBIOS)/os/hal/ports/$(CHIBIOS_PLATFORM)/$(CHIBIOS_DEVICE_FAMILY)/platform.mk
include $(CHIBIOS)/os/hal/osal/rt/osal.mk

# RTOS files (optional).
include $(CHIBIOS)/os/rt/rt.mk
include $(CHIBIOS)/os/common/ports/$(CHIBIOS_CPUCLASS)/compilers/GCC/mk/port_$(CHIBIOS_PORT).mk

# Specific board files
ifneq ($(CHIBIOS_BOARD),)
  include $(CHIBIOS)/os/hal/boards/$(CHIBIOS_BOARD)/board.mk
endif
LIBPATH += $(CHIBIOS)/os/common/startup/$(CHIBIOS_CPUCLASS)/compilers/GCC/ld

ifeq ($(LDSCRIPT),)
  ifneq ($(CHIBIOS_LDSCRIPT),)
    LDSCRIPT= $(STARTUPLD)/$(CHIBIOS_LDSCRIPT)
  endif
endif

ifneq ($(LDSCRIPT),)
  ifeq ($(CHIBIOS_PROCESS_STACKSIZE),)
    LDFLAGS += -Wl,--defsym=__process_stack_size__=0x400
  else
    LDFLAGS += -Wl,--defsym=__process_stack_size__=$(CHIBIOS_PROCESS_STACKSIZE)
  endif
  ifeq ($(CHIBIOS_EXCEPTIONS_STACKSIZE),)
    LDFLAGS += -Wl,--defsym=__main_stack_size__=0x400
  else
    LDFLAGS += -Wl,--defsym=__main_stack_size__=$(CHIBIOS_EXCEPTIONS_STACKSIZE)
  endif
endif

ifeq ($(CHIBIOS_FATFS),1)
  include $(CHIBIOS)/os/various/fatfs_bindings/fatfs.mk
  INCPATH += $(FATFSINC)
  SRC += $(FATFSSRC)
endif

ifeq ($(CHIBIOS_LWIP),1)
  include $(CHIBIOS)/os/various/lwip_bindings/lwip.mk
  INCPATH += $(LWINC) \
	     $(CHIBIOS)/os/various
  SRC += $(LWSRC) \
	 $(CHIBIOS)/os/various/evtimer.c
endif

# Add include files
INCPATH +=	$(CHIBIOS)/os/license \
			$(STARTUPINC) \
            $(KERNINC) \
            $(PORTINC) \
            $(OSALINC) \
            $(HALINC) \
            $(PLATFORMINC) \
            $(BOARDINC)

# Add C files
SRC  += $(STARTUPSRC) \
        $(KERNSRC) \
        $(PORTSRC) \
        $(OSALSRC) \
        $(HALSRC) \
        $(PLATFORMSRC) \
        $(BOARDSRC)

# Add ASM files
SRC  += $(STARTUPASM) $(PORTASM) $(OSALASM)
