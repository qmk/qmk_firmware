# Hey Emacs, this is a -*- makefile -*-
##############################################################################
# Architecture or project specific options
#

# Stack size to be allocated to the Cortex-M process stack. This stack is
# the stack used by the main() thread.
ifeq ($(USE_PROCESS_STACKSIZE),)
  USE_PROCESS_STACKSIZE = 0x800
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
OPT_OS = chibios
CHIBIOS = $(TOP_DIR)/lib/chibios
CHIBIOS_CONTRIB = $(TOP_DIR)/lib/chibios-contrib
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

ifeq ("$(PLATFORM_NAME)","")
	PLATFORM_NAME = platform
endif

PLATFORM_MK = $(CHIBIOS)/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)/$(PLATFORM_NAME).mk
ifeq ("$(wildcard $(PLATFORM_MK))","")
PLATFORM_MK = $(CHIBIOS_CONTRIB)/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)/$(PLATFORM_NAME).mk
endif
include $(PLATFORM_MK)

BOARD_MK :=

ifneq ("$(wildcard $(KEYBOARD_PATH_5)/boards/$(BOARD)/board.mk)","")
    BOARD_PATH = $(KEYBOARD_PATH_5)
    BOARD_MK += $(KEYBOARD_PATH_5)/boards/$(BOARD)/board.mk
else ifneq ("$(wildcard $(KEYBOARD_PATH_4)/boards/$(BOARD)/board.mk)","")
    BOARD_PATH = $(KEYBOARD_PATH_4)
    BOARD_MK += $(KEYBOARD_PATH_4)/boards/$(BOARD)/board.mk
else ifneq ("$(wildcard $(KEYBOARD_PATH_3)/boards/$(BOARD)/board.mk)","")
    BOARD_PATH = $(KEYBOARD_PATH_3)
    BOARD_MK += $(KEYBOARD_PATH_3)/boards/$(BOARD)/board.mk
else ifneq ("$(wildcard $(KEYBOARD_PATH_2)/boards/$(BOARD)/board.mk)","")
    BOARD_PATH = $(KEYBOARD_PATH_2)
    BOARD_MK += $(KEYBOARD_PATH_2)/boards/$(BOARD)/board.mk
else ifneq ("$(wildcard $(KEYBOARD_PATH_1)/boards/$(BOARD)/board.mk)","")
    BOARD_PATH = $(KEYBOARD_PATH_1)
    BOARD_MK += $(KEYBOARD_PATH_1)/boards/$(BOARD)/board.mk
else ifneq ("$(wildcard $(TOP_DIR)/platforms/chibios/$(BOARD)/board/board.mk)","")
    BOARD_PATH = $(TOP_DIR)/platforms/chibios/$(BOARD)
    BOARD_MK += $(TOP_DIR)/platforms/chibios/$(BOARD)/board/board.mk
    KEYBOARD_PATHS += $(BOARD_PATH)/configs
endif

ifeq ("$(wildcard $(BOARD_MK))","")
	BOARD_MK = $(CHIBIOS)/os/hal/boards/$(BOARD)/board.mk
	ifeq ("$(wildcard $(BOARD_MK))","")
		BOARD_MK = $(CHIBIOS_CONTRIB)/os/hal/boards/$(BOARD)/board.mk
	endif
endif

# Bootloader address
ifdef STM32_BOOTLOADER_ADDRESS
    OPT_DEFS += -DSTM32_BOOTLOADER_ADDRESS=$(STM32_BOOTLOADER_ADDRESS)
endif

# Work out if we need to set up the include for the bootloader definitions
ifneq ("$(wildcard $(KEYBOARD_PATH_5)/bootloader_defs.h)","")
    OPT_DEFS += -include $(KEYBOARD_PATH_5)/bootloader_defs.h
else ifneq ("$(wildcard $(KEYBOARD_PATH_5)/boards/$(BOARD)/bootloader_defs.h)","")
    OPT_DEFS += -include $(KEYBOARD_PATH_5)/boards/$(BOARD)/bootloader_defs.h
else ifneq ("$(wildcard $(KEYBOARD_PATH_4)/bootloader_defs.h)","")
    OPT_DEFS += -include $(KEYBOARD_PATH_4)/bootloader_defs.h
else ifneq ("$(wildcard $(KEYBOARD_PATH_4)/boards/$(BOARD)/bootloader_defs.h)","")
    OPT_DEFS += -include $(KEYBOARD_PATH_4)/boards/$(BOARD)/bootloader_defs.h
else ifneq ("$(wildcard $(KEYBOARD_PATH_3)/bootloader_defs.h)","")
    OPT_DEFS += -include $(KEYBOARD_PATH_3)/bootloader_defs.h
else ifneq ("$(wildcard $(KEYBOARD_PATH_3)/boards/$(BOARD)/bootloader_defs.h)","")
    OPT_DEFS += -include $(KEYBOARD_PATH_3)/boards/$(BOARD)/bootloader_defs.h
else ifneq ("$(wildcard $(KEYBOARD_PATH_2)/bootloader_defs.h)","")
    OPT_DEFS += -include $(KEYBOARD_PATH_2)/bootloader_defs.h
else ifneq ("$(wildcard $(KEYBOARD_PATH_2)/boards/$(BOARD)/bootloader_defs.h)","")
    OPT_DEFS += -include $(KEYBOARD_PATH_2)/boards/$(BOARD)/bootloader_defs.h
else ifneq ("$(wildcard $(KEYBOARD_PATH_1)/bootloader_defs.h)","")
    OPT_DEFS += -include $(KEYBOARD_PATH_1)/bootloader_defs.h
else ifneq ("$(wildcard $(KEYBOARD_PATH_1)/boards/$(BOARD)/bootloader_defs.h)","")
    OPT_DEFS += -include $(KEYBOARD_PATH_1)/boards/$(BOARD)/bootloader_defs.h
else ifneq ("$(wildcard $(BOARD_PATH)/configs/bootloader_defs.h)","")
    OPT_DEFS += -include $(BOARD_PATH)/configs/bootloader_defs.h
endif

# Work out the config file directories
ifneq ("$(wildcard $(KEYBOARD_PATH_5)/chconf.h)","")
    CHCONFDIR = $(KEYBOARD_PATH_5)
else ifneq ("$(wildcard $(KEYBOARD_PATH_4)/chconf.h)","")
    CHCONFDIR = $(KEYBOARD_PATH_4)
else ifneq ("$(wildcard $(KEYBOARD_PATH_3)/chconf.h)","")
    CHCONFDIR = $(KEYBOARD_PATH_3)
else ifneq ("$(wildcard $(KEYBOARD_PATH_2)/chconf.h)","")
    CHCONFDIR = $(KEYBOARD_PATH_2)
else ifneq ("$(wildcard $(KEYBOARD_PATH_1)/chconf.h)","")
    CHCONFDIR = $(KEYBOARD_PATH_1)
else ifneq ("$(wildcard $(TOP_DIR)/platforms/chibios/$(BOARD)/configs/chconf.h)","")
    CHCONFDIR = $(TOP_DIR)/platforms/chibios/$(BOARD)/configs
else ifneq ("$(wildcard $(TOP_DIR)/platforms/chibios/common/configs/chconf.h)","")
    CHCONFDIR = $(TOP_DIR)/platforms/chibios/common/configs
endif

ifneq ("$(wildcard $(KEYBOARD_PATH_5)/halconf.h)","")
    HALCONFDIR = $(KEYBOARD_PATH_5)
else ifneq ("$(wildcard $(KEYBOARD_PATH_4)/halconf.h)","")
    HALCONFDIR = $(KEYBOARD_PATH_4)
else ifneq ("$(wildcard $(KEYBOARD_PATH_3)/halconf.h)","")
    HALCONFDIR = $(KEYBOARD_PATH_3)
else ifneq ("$(wildcard $(KEYBOARD_PATH_2)/halconf.h)","")
    HALCONFDIR = $(KEYBOARD_PATH_2)
else ifneq ("$(wildcard $(KEYBOARD_PATH_1)/halconf.h)","")
    HALCONFDIR = $(KEYBOARD_PATH_1)
else ifneq ("$(wildcard $(TOP_DIR)/platforms/chibios/$(BOARD)/configs/halconf.h)","")
    HALCONFDIR = $(TOP_DIR)/platforms/chibios/$(BOARD)/configs
else ifneq ("$(wildcard $(TOP_DIR)/platforms/chibios/common/configs/halconf.h)","")
    HALCONFDIR = $(TOP_DIR)/platforms/chibios/common/configs
endif

# HAL-OSAL files (optional).
include $(CHIBIOS)/os/hal/hal.mk

ifeq ("$(PLATFORM_NAME)","")
	PLATFORM_NAME = platform
endif

PLATFORM_MK = $(CHIBIOS)/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)/$(PLATFORM_NAME).mk
ifeq ("$(wildcard $(PLATFORM_MK))","")
PLATFORM_MK = $(CHIBIOS_CONTRIB)/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)/$(PLATFORM_NAME).mk
endif
include $(PLATFORM_MK)


include $(BOARD_MK)
-include $(CHIBIOS)/os/hal/osal/rt/osal.mk         # ChibiOS <= 19.x
-include $(CHIBIOS)/os/hal/osal/rt-nil/osal.mk     # ChibiOS >= 20.x
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

RULESPATH = $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC
ifeq ("$(wildcard $(RULESPATH)/rules.mk)","")
RULESPATH = $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC
endif

# Define linker script file here
ifneq ("$(wildcard $(KEYBOARD_PATH_5)/ld/$(MCU_LDSCRIPT).ld)","")
    LDSCRIPT = $(KEYBOARD_PATH_5)/ld/$(MCU_LDSCRIPT).ld
else ifneq ("$(wildcard $(KEYBOARD_PATH_4)/ld/$(MCU_LDSCRIPT).ld)","")
    LDSCRIPT = $(KEYBOARD_PATH_4)/ld/$(MCU_LDSCRIPT).ld
else ifneq ("$(wildcard $(KEYBOARD_PATH_3)/ld/$(MCU_LDSCRIPT).ld)","")
    LDSCRIPT = $(KEYBOARD_PATH_3)/ld/$(MCU_LDSCRIPT).ld
else ifneq ("$(wildcard $(KEYBOARD_PATH_2)/ld/$(MCU_LDSCRIPT).ld)","")
    LDSCRIPT = $(KEYBOARD_PATH_2)/ld/$(MCU_LDSCRIPT).ld
else ifneq ("$(wildcard $(KEYBOARD_PATH_1)/ld/$(MCU_LDSCRIPT).ld)","")
    LDSCRIPT = $(KEYBOARD_PATH_1)/ld/$(MCU_LDSCRIPT).ld
else ifneq ("$(wildcard $(TOP_DIR)/platforms/chibios/common/ld/$(MCU_LDSCRIPT).ld)","")
    LDSCRIPT = $(TOP_DIR)/platforms/chibios/common/ld/$(MCU_LDSCRIPT).ld
else ifneq ("$(wildcard $(STARTUPLD_CONTRIB)/$(MCU_LDSCRIPT).ld)","")
    LDSCRIPT = $(STARTUPLD_CONTRIB)/$(MCU_LDSCRIPT).ld
    USE_CHIBIOS_CONTRIB = yes
else
    LDSCRIPT = $(STARTUPLD)/$(MCU_LDSCRIPT).ld
endif

CHIBISRC = $(STARTUPSRC) \
       $(KERNSRC) \
       $(PORTSRC) \
       $(OSALSRC) \
       $(HALSRC) \
       $(PLATFORMSRC) \
       $(BOARDSRC) \
       $(STREAMSSRC) \
       $(CHIBIOS)/os/various/syscalls.c

# Ensure the ASM files are not subjected to LTO -- it'll strip out interrupt handlers otherwise.
QUANTUM_LIB_SRC += $(STARTUPASM) $(PORTASM) $(OSALASM)

CHIBISRC := $(patsubst $(TOP_DIR)/%,%,$(CHIBISRC))

EXTRAINCDIRS += $(CHIBIOS)/os/license $(CHIBIOS)/os/oslib/include \
         $(TOP_DIR)/platforms/chibios/$(BOARD)/configs \
         $(TOP_DIR)/platforms/chibios/common/configs \
         $(HALCONFDIR) $(CHCONFDIR) \
         $(STARTUPINC) $(KERNINC) $(PORTINC) $(OSALINC) \
         $(HALINC) $(PLATFORMINC) $(BOARDINC) $(TESTINC) \
         $(STREAMSINC) $(CHIBIOS)/os/various $(COMMON_VPATH)

#
# ChibiOS-Contrib
##############################################################################

# Work out if we're using ChibiOS-Contrib by checking if halconf_community.h exists
ifneq ("$(wildcard $(KEYBOARD_PATH_5)/halconf_community.h)","")
    USE_CHIBIOS_CONTRIB = yes
else ifneq ("$(wildcard $(KEYBOARD_PATH_4)/halconf_community.h)","")
    USE_CHIBIOS_CONTRIB = yes
else ifneq ("$(wildcard $(KEYBOARD_PATH_3)/halconf_community.h)","")
    USE_CHIBIOS_CONTRIB = yes
else ifneq ("$(wildcard $(KEYBOARD_PATH_2)/halconf_community.h)","")
    USE_CHIBIOS_CONTRIB = yes
else ifneq ("$(wildcard $(KEYBOARD_PATH_1)/halconf_community.h)","")
    USE_CHIBIOS_CONTRIB = yes
else ifneq ("$(wildcard $(TOP_DIR)/platforms/chibios/$(BOARD)/configs/halconf_community.h)","")
    USE_CHIBIOS_CONTRIB = yes
endif

ifeq ($(strip $(USE_CHIBIOS_CONTRIB)),yes)
	include $(CHIBIOS_CONTRIB)/os/hal/hal.mk
	CHIBISRC += $(PLATFORMSRC_CONTRIB) $(HALSRC_CONTRIB)
	EXTRAINCDIRS += $(PLATFORMINC_CONTRIB) $(HALINC_CONTRIB) $(CHIBIOS_CONTRIB)/os/various
endif

#
# Project, sources and paths
##############################################################################

##############################################################################
# Injected configs
#
ifneq ("$(wildcard $(BOARD_PATH)/configs/config.h)","")
    CONFIG_H += $(BOARD_PATH)/configs/config.h
endif
ifneq ("$(wildcard $(BOARD_PATH)/configs/post_config.h)","")
    POST_CONFIG_H += $(BOARD_PATH)/configs/post_config.h
endif

##############################################################################
# Compiler settings
#
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
AR = arm-none-eabi-ar
NM = arm-none-eabi-nm
HEX = $(OBJCOPY) -O $(FORMAT)
EEP =
BIN = $(OBJCOPY) -O binary

COMMON_VPATH += $(DRIVER_PATH)/chibios

THUMBFLAGS = -DTHUMB_PRESENT -mno-thumb-interwork -DTHUMB_NO_INTERWORKING -mthumb -DTHUMB

COMPILEFLAGS += -fomit-frame-pointer
COMPILEFLAGS += -falign-functions=16
COMPILEFLAGS += -ffunction-sections
COMPILEFLAGS += -fdata-sections
COMPILEFLAGS += -fno-common
COMPILEFLAGS += -fshort-wchar
COMPILEFLAGS += $(THUMBFLAGS)

# FPU options default (Cortex-M4 and Cortex-M7 single precision).
USE_FPU_OPT ?= -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant

# FPU-related options
USE_FPU ?= no
ifneq ($(USE_FPU),no)
  COMPILEFLAGS += $(USE_FPU_OPT)
  OPT_DEFS += -DCORTEX_USE_FPU=TRUE
else
  OPT_DEFS += -DCORTEX_USE_FPU=FALSE
endif

CFLAGS += $(COMPILEFLAGS)

ASFLAGS += $(THUMBFLAGS)

CXXFLAGS += $(COMPILEFLAGS)
CXXFLAGS += -fno-rtti

LDFLAGS +=-Wl,--gc-sections
LDFLAGS +=-Wl,--no-wchar-size-warning
LDFLAGS += -mno-thumb-interwork -mthumb
LDSYMBOLS =,--defsym=__process_stack_size__=$(USE_PROCESS_STACKSIZE)
LDSYMBOLS :=$(LDSYMBOLS),--defsym=__main_stack_size__=$(USE_EXCEPTIONS_STACKSIZE)
LDFLAGS += -Wl,--script=$(LDSCRIPT)$(LDSYMBOLS)

OPT_DEFS += -DPROTOCOL_CHIBIOS

# Workaround to stop ChibiOS from complaining about new GCC -- it's been fixed for 7/8/9 already
OPT_DEFS += -DPORT_IGNORE_GCC_VERSION_CHECK=1

MCUFLAGS = -mcpu=$(MCU)

DEBUG = gdb

DFU_ARGS ?=
ifneq ("$(SERIAL)","")
	DFU_ARGS += -S $(SERIAL)
endif

ST_LINK_ARGS ?=
ST_FLASH_ARGS ?=

# List any extra directories to look for libraries here.
EXTRALIBDIRS = $(RULESPATH)/ld

DFU_UTIL ?= dfu-util
ST_LINK_CLI ?= st-link_cli
ST_FLASH ?= st-flash

define EXEC_DFU_UTIL
	until $(DFU_UTIL) -l | grep -q "Found DFU"; do\
		printf "$(MSG_BOOTLOADER_NOT_FOUND)" ;\
		sleep 5 ;\
	done
	$(DFU_UTIL) $(DFU_ARGS) -D $(BUILD_DIR)/$(TARGET).bin
endef

dfu-util: $(BUILD_DIR)/$(TARGET).bin cpfirmware sizeafter
	$(call EXEC_DFU_UTIL)

# Legacy alias
dfu-util-wait: dfu-util

# TODO: Remove once ARM has a way to configure EECONFIG_HANDEDNESS
#       within the emulated eeprom via dfu-util or another tool
ifneq (,$(filter $(MAKECMDGOALS),dfu-util-split-left))
    OPT_DEFS += -DINIT_EE_HANDS_LEFT
endif

ifneq (,$(filter $(MAKECMDGOALS),dfu-util-split-right))
    OPT_DEFS += -DINIT_EE_HANDS_RIGHT
endif

dfu-util-split-left: dfu-util

dfu-util-split-right: dfu-util


st-link-cli: $(BUILD_DIR)/$(TARGET).hex sizeafter
	$(ST_LINK_CLI) $(ST_LINK_ARGS) -q -c SWD -p $(BUILD_DIR)/$(TARGET).hex -Rst

st-flash: $(BUILD_DIR)/$(TARGET).hex sizeafter
	$(ST_FLASH) $(ST_FLASH_ARGS) --reset --format ihex write $(BUILD_DIR)/$(TARGET).hex


# Autodetect teensy loader
ifndef TEENSY_LOADER_CLI
    ifneq (, $(shell which teensy-loader-cli 2>/dev/null))
        TEENSY_LOADER_CLI ?= teensy-loader-cli
    else
        TEENSY_LOADER_CLI ?= teensy_loader_cli
    endif
endif

define EXEC_TEENSY
	$(TEENSY_LOADER_CLI) -mmcu=$(MCU_LDSCRIPT) -w -v $(BUILD_DIR)/$(TARGET).hex
endef

teensy: $(BUILD_DIR)/$(TARGET).hex cpfirmware sizeafter
	$(call EXEC_TEENSY)

bin: $(BUILD_DIR)/$(TARGET).bin sizeafter
	$(COPY) $(BUILD_DIR)/$(TARGET).bin $(TARGET).bin;


flash: $(BUILD_DIR)/$(TARGET).bin cpfirmware sizeafter
ifneq ($(strip $(PROGRAM_CMD)),)
	$(PROGRAM_CMD)
else ifeq ($(strip $(BOOTLOADER)),kiibohd)
	$(call EXEC_DFU_UTIL)
else ifeq ($(strip $(MCU_FAMILY)),KINETIS)
	$(call EXEC_TEENSY)
else ifeq ($(strip $(MCU_FAMILY)),STM32)
	$(call EXEC_DFU_UTIL)
else
	$(PRINT_OK); $(SILENT) || printf "$(MSG_FLASH_BOOTLOADER)"
endif
