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
else ifneq ("$(wildcard $(TOP_DIR)/drivers/boards/$(BOARD)/board.mk)","")
    BOARD_PATH = $(TOP_DIR)/drivers
    BOARD_MK += $(TOP_DIR)/drivers/boards/$(BOARD)/board.mk
endif

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
	   $(STARTUPASM) \
	   $(PORTASM) \
	   $(OSALASM)

CHIBISRC := $(patsubst $(TOP_DIR)/%,%,$(CHIBISRC))

EXTRAINCDIRS += $(CHIBIOS)/os/license \
         $(STARTUPINC) $(KERNINC) $(PORTINC) $(OSALINC) \
         $(HALINC) $(PLATFORMINC) $(BOARDINC) $(TESTINC) \
         $(STREAMSINC) $(CHIBIOS)/os/various $(COMMON_VPATH)

#
# Project, sources and paths
##############################################################################


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

COMMON_VPATH += $(DRIVER_PATH)/arm

THUMBFLAGS = -DTHUMB_PRESENT -mno-thumb-interwork -DTHUMB_NO_INTERWORKING -mthumb -DTHUMB

COMPILEFLAGS += -fomit-frame-pointer
COMPILEFLAGS += -falign-functions=16
COMPILEFLAGS += -ffunction-sections
COMPILEFLAGS += -fdata-sections
COMPILEFLAGS += -fno-common
COMPILEFLAGS += -fshort-wchar
COMPILEFLAGS += $(THUMBFLAGS)

CFLAGS += $(COMPILEFLAGS)

ASFLAGS += $(THUMBFLAGS)

CPPFLAGS += $(COMPILEFLAGS)
CPPFLAGS += -fno-rtti

LDFLAGS +=-Wl,--gc-sections
LDFLAGS +=-Wl,--no-wchar-size-warning
LDFLAGS += -mno-thumb-interwork -mthumb
LDSYMBOLS =,--defsym=__process_stack_size__=$(USE_PROCESS_STACKSIZE)
LDSYMBOLS :=$(LDSYMBOLS),--defsym=__main_stack_size__=$(USE_EXCEPTIONS_STACKSIZE)
LDFLAGS += -Wl,--script=$(LDSCRIPT)$(LDSYMBOLS)

OPT_DEFS += -DPROTOCOL_CHIBIOS

MCUFLAGS = -mcpu=$(MCU)

# FPU options default (Cortex-M4 and Cortex-M7 single precision).
ifeq ($(USE_FPU_OPT),)
  USE_FPU_OPT = -mfloat-abi=$(USE_FPU) -mfpu=fpv4-sp-d16 -fsingle-precision-constant
endif

# FPU-related options
ifeq ($(USE_FPU),)
  USE_FPU = no
endif
ifneq ($(USE_FPU),no)
  OPT    += $(USE_FPU_OPT)
  OPT_DEFS  += -DCORTEX_USE_FPU=TRUE
else
  OPT_DEFS  += -DCORTEX_USE_FPU=FALSE
endif

DEBUG = gdb

DFU_ARGS ?=
ifneq ("$(SERIAL)","")
	DFU_ARGS += -S $(SERIAL)
endif

ST_LINK_ARGS ?=

# List any extra directories to look for libraries here.
EXTRALIBDIRS = $(RULESPATH)/ld

DFU_UTIL ?= dfu-util
ST_LINK_CLI ?= st-link_cli

# Generate a .qmk for the QMK-FF
qmk: $(BUILD_DIR)/$(TARGET).bin
	zip $(TARGET).qmk -FSrj $(KEYMAP_PATH)/*
	zip $(TARGET).qmk -u $<
	printf "@ $<\n@=firmware.bin\n" | zipnote -w $(TARGET).qmk
	printf "{\n  \"generated\": \"%s\"\n}" "$$(date)" > $(BUILD_DIR)/$(TARGET).json
	if [ -f $(KEYBOARD_PATH_5)/info.json ]; then \
		jq -s '.[0] * .[1]' $(BUILD_DIR)/$(TARGET).json $(KEYBOARD_PATH_5)/info.json | ex -sc 'wq!$(BUILD_DIR)/$(TARGET).json' /dev/stdin; \
	fi
	if [ -f $(KEYBOARD_PATH_4)/info.json ]; then \
		jq -s '.[0] * .[1]' $(BUILD_DIR)/$(TARGET).json $(KEYBOARD_PATH_4)/info.json | ex -sc 'wq!$(BUILD_DIR)/$(TARGET).json' /dev/stdin; \
	fi
	if [ -f $(KEYBOARD_PATH_3)/info.json ]; then \
		jq -s '.[0] * .[1]' $(BUILD_DIR)/$(TARGET).json $(KEYBOARD_PATH_3)/info.json | ex -sc 'wq!$(BUILD_DIR)/$(TARGET).json' /dev/stdin; \
	fi
	if [ -f $(KEYBOARD_PATH_2)/info.json ]; then \
		jq -s '.[0] * .[1]' $(BUILD_DIR)/$(TARGET).json $(KEYBOARD_PATH_2)/info.json | ex -sc 'wq!$(BUILD_DIR)/$(TARGET).json' /dev/stdin; \
	fi
	if [ -f $(KEYBOARD_PATH_1)/info.json ]; then \
		jq -s '.[0] * .[1]' $(BUILD_DIR)/$(TARGET).json $(KEYBOARD_PATH_1)/info.json | ex -sc 'wq!$(BUILD_DIR)/$(TARGET).json' /dev/stdin; \
	fi
	zip $(TARGET).qmk -urj $(BUILD_DIR)/$(TARGET).json
	printf "@ $(TARGET).json\n@=info.json\n" | zipnote -w $(TARGET).qmk

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
ifeq ($(strip $(BOOTLOADER)),dfu)
	$(call EXEC_DFU_UTIL)
else ifeq ($(strip $(MCU_FAMILY)),KINETIS)
	$(call EXEC_TEENSY)
else ifeq ($(strip $(MCU_FAMILY)),STM32)
	$(call EXEC_DFU_UTIL)
else
	$(PRINT_OK); $(SILENT) || printf "$(MSG_FLASH_BOOTLOADER)"
endif
