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

#
# Startup, Port and Platform support selection
##############################################################################

ifeq ($(strip $(MCU)), risc-v)
    # RISC-V Support
    # As of 4.7.2021 there is only one supported RISC-V platform in Chibios-Contrib,
    # therefore all required settings are hard-coded
    STARTUP_MK = $(CHIBIOS_CONTRIB)/os/common/startup/RISCV-ECLIC/compilers/GCC/mk/startup_$(MCU_STARTUP).mk
    PORT_V = $(CHIBIOS_CONTRIB)/os/common/ports/RISCV-ECLIC/compilers/GCC/mk/port.mk
    RULESPATH = $(CHIBIOS_CONTRIB)/os/common/startup/RISCV-ECLIC/compilers/GCC
else
    # ARM Support
    # Startup files. Try a few different locations, for compability with old versions and
    # for things hardware in the contrib repository
    STARTUP_MK = $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/startup_$(MCU_STARTUP).mk
    ifeq ("$(wildcard $(STARTUP_MK))","")
        STARTUP_MK = $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_$(MCU_STARTUP).mk
        ifeq ("$(wildcard $(STARTUP_MK))","")
            STARTUP_MK = $(CHIBIOS_CONTRIB)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_$(MCU_STARTUP).mk
        endif
    endif

    # Compability with old version
    PORT_V = $(CHIBIOS)/os/rt/ports/ARMCMx/compilers/GCC/mk/port_v$(ARMV)m.mk
    ifeq ("$(wildcard $(PORT_V))","")
    PORT_V = $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/port_v$(ARMV)m.mk
    endif

    RULESPATH = $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC
    ifeq ("$(wildcard $(RULESPATH)/rules.mk)","")
    RULESPATH = $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC
    endif
endif

ifeq ("$(PLATFORM_NAME)","")
    PLATFORM_NAME = platform
endif

PLATFORM_MK = $(CHIBIOS)/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)/$(PLATFORM_NAME).mk
ifeq ("$(wildcard $(PLATFORM_MK))","")
PLATFORM_MK = $(CHIBIOS_CONTRIB)/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)/$(PLATFORM_NAME).mk
endif

include $(STARTUP_MK)
include $(PORT_V)
include $(PLATFORM_MK)

#
# Board support selection.
##############################################################################

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
    ifneq ("$(wildcard $(BOARD_PATH)/rules.mk)","")
        include $(BOARD_PATH)/rules.mk
    endif
endif

ifeq ("$(wildcard $(BOARD_MK))","")
    BOARD_MK = $(CHIBIOS)/os/hal/boards/$(BOARD)/board.mk
    ifeq ("$(wildcard $(BOARD_MK))","")
        BOARD_MK = $(CHIBIOS_CONTRIB)/os/hal/boards/$(BOARD)/board.mk
    endif
endif

include $(BOARD_MK)

#
# Bootloader selection.
##############################################################################

# Set bootloader address if supplied.
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

#
# ChibiOS config selection.
##############################################################################

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

#
# HAL config selection.
##############################################################################

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

#
# Linker script selection.
##############################################################################

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
else ifneq ("$(wildcard $(TOP_DIR)/platforms/chibios/$(BOARD)/ld/$(MCU_LDSCRIPT).ld)","")
    LDSCRIPT = $(TOP_DIR)/platforms/chibios/$(BOARD)/ld/$(MCU_LDSCRIPT).ld
else ifneq ("$(wildcard $(TOP_DIR)/platforms/chibios/common/ld/$(MCU_LDSCRIPT).ld)","")
    LDSCRIPT = $(TOP_DIR)/platforms/chibios/common/ld/$(MCU_LDSCRIPT).ld
else ifneq ("$(wildcard $(STARTUPLD_CONTRIB)/$(MCU_LDSCRIPT).ld)","")
    LDSCRIPT = $(STARTUPLD_CONTRIB)/$(MCU_LDSCRIPT).ld
    USE_CHIBIOS_CONTRIB = yes
else
    LDSCRIPT = $(STARTUPLD)/$(MCU_LDSCRIPT).ld
endif

#
# Include ChibiOS makefiles.
##############################################################################

# HAL-OSAL files (optional).
include $(CHIBIOS)/os/hal/hal.mk
-include $(CHIBIOS)/os/hal/osal/rt/osal.mk         # ChibiOS <= 19.x
-include $(CHIBIOS)/os/hal/osal/rt-nil/osal.mk     # ChibiOS >= 20.x
# RTOS files (optional).
include $(CHIBIOS)/os/rt/rt.mk
# Other files (optional).
include $(CHIBIOS)/os/hal/lib/streams/streams.mk

CHIBISRC = $(STARTUPSRC) \
       $(KERNSRC) \
       $(PORTSRC) \
       $(OSALSRC) \
       $(HALSRC) \
       $(PLATFORMSRC) \
       $(BOARDSRC) \
       $(STREAMSSRC) \
       $(CHIBIOS)/os/various/syscalls.c \
       $(PLATFORM_COMMON_DIR)/syscall-fallbacks.c

# Ensure the ASM files are not subjected to LTO -- it'll strip out interrupt handlers otherwise.
QUANTUM_LIB_SRC += $(STARTUPASM) $(PORTASM) $(OSALASM) $(PLATFORMASM)

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
#

# Shared Compiler flags for all toolchains
COMPILEFLAGS += -fomit-frame-pointer
COMPILEFLAGS += -ffunction-sections
COMPILEFLAGS += -fdata-sections
COMPILEFLAGS += -fno-common
COMPILEFLAGS += -fshort-wchar

# Shared Linker flags for all toolchains
LDFLAGS += -Wl,--script=$(LDSCRIPT)$(LDSYMBOLS)
LDFLAGS +=-Wl,--gc-sections

# Define stack size of main thread
LDSYMBOLS =,--defsym=__process_stack_size__=$(USE_PROCESS_STACKSIZE)
LDSYMBOLS :=$(LDSYMBOLS),--defsym=__main_stack_size__=$(USE_EXCEPTIONS_STACKSIZE)

# RISC-V toolchain specific configuration
ifeq ($(strip $(MCU)), risc-v)
    ifeq ($(strip $(TOOLCHAIN)),)
        ifneq ($(shell which riscv32-unknown-elf-gcc 2>/dev/null),)
            TOOLCHAIN ?= riscv32-unknown-elf-
        else
            ifneq ($(shell which riscv64-unknown-elf-gcc 2>/dev/null),)
                TOOLCHAIN ?= riscv64-unknown-elf-
            else
                $(error "No RISC-V toolchain found. Can't find riscv32-unknown-elf-gcc or riscv64-unknown-elf-gcc found in your systems PATH variable. Please install a valid toolchain and make it accessible!")
            endif
        endif
    endif

    COMPILEFLAGS += -mstrict-align    
    LDFLAGS      += -nostartfiles -mstrict-align

    MCUFLAGS     += -march=$(MCU_ARCH)
    MCUFLAGS     += -mabi=$(MCU_ABI)
    MCUFLAGS     += -mcmodel=$(MCU_CMODEL)
else
# ARM toolchain specific configuration
    TOOLCHAIN ?= arm-none-eabi-

    THUMBFLAGS = -DTHUMB_PRESENT -mno-thumb-interwork -DTHUMB_NO_INTERWORKING -mthumb -DTHUMB

    COMPILEFLAGS += -falign-functions=16
    COMPILEFLAGS += $(THUMBFLAGS)

    LDFLAGS += -mno-thumb-interwork -mthumb
    LDFLAGS += -Wl,--no-wchar-size-warning
    LDFLAGS += --specs=nano.specs
    ASFLAGS += $(THUMBFLAGS)

    MCUFLAGS = -mcpu=$(MCU)

    # FPU-related options
    USE_FPU ?= no
    ifneq ($(USE_FPU),no)
        # FPU options default (Cortex-M4 and Cortex-M7 single precision).
        USE_FPU_OPT ?= -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant
        COMPILEFLAGS += $(USE_FPU_OPT)
        OPT_DEFS += -DCORTEX_USE_FPU=TRUE
    else
        OPT_DEFS += -DCORTEX_USE_FPU=FALSE
    endif
endif

# GCC Toolchain 
CC      = $(TOOLCHAIN)gcc
OBJCOPY = $(TOOLCHAIN)objcopy
OBJDUMP = $(TOOLCHAIN)objdump
SIZE    = $(TOOLCHAIN)size
AR      = $(TOOLCHAIN)ar
NM      = $(TOOLCHAIN)nm
HEX     = $(OBJCOPY) -O $(FORMAT)
EEP     =
BIN     = $(OBJCOPY) -O binary

COMMON_VPATH += $(DRIVER_PATH)/chibios

# C Compiler flags
CFLAGS += $(COMPILEFLAGS)

# C++ Compiler flags
CXXFLAGS += $(COMPILEFLAGS)
CXXFLAGS += -fno-rtti

OPT_DEFS += -DPROTOCOL_CHIBIOS

# Workaround to stop ChibiOS from complaining about new GCC -- it's been fixed for 7/8/9 already
OPT_DEFS += -DPORT_IGNORE_GCC_VERSION_CHECK=1

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
	if ! $(DFU_UTIL) -l | grep -q "Found DFU"; then \
		printf "$(MSG_BOOTLOADER_NOT_FOUND_QUICK_RETRY)" ;\
		sleep $(BOOTLOADER_RETRY_TIME) ;\
		while ! $(DFU_UTIL) -l | grep -q "Found DFU"; do \
			printf "." ;\
			sleep $(BOOTLOADER_RETRY_TIME) ;\
		done ;\
		printf "\n" ;\
	fi
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

TEENSY_LOADER_CLI_MCU ?= $(MCU_LDSCRIPT)

define EXEC_TEENSY
	$(TEENSY_LOADER_CLI) -mmcu=$(TEENSY_LOADER_CLI_MCU) -w -v $(BUILD_DIR)/$(TARGET).hex
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
else ifeq ($(strip $(MCU_FAMILY)),MIMXRT1062)
	$(call EXEC_TEENSY)
else ifeq ($(strip $(MCU_FAMILY)),STM32)
	$(call EXEC_DFU_UTIL)
else ifeq ($(strip $(MCU_FAMILY)),GD)
	$(call EXEC_DFU_UTIL)
else
	$(PRINT_OK); $(SILENT) || printf "$(MSG_FLASH_BOOTLOADER)"
endif
