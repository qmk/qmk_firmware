ifndef VERBOSE
.SILENT:
endif

.DEFAULT_GOAL := all

include common.mk

ifneq ($(SUBPROJECT),)
    TARGET ?= $(KEYBOARD)_$(SUBPROJECT)_$(KEYMAP)
    KEYBOARD_OUTPUT := $(BUILD_DIR)/obj_$(KEYBOARD)_$(SUBPROJECT)
else
    TARGET ?= $(KEYBOARD)_$(KEYMAP)
    KEYBOARD_OUTPUT := $(BUILD_DIR)/obj_$(KEYBOARD)
endif

# Force expansion
TARGET := $(TARGET)


MASTER ?= left
ifdef master
    MASTER = $(master)
endif

ifeq ($(MASTER),right)
    OPT_DEFS += -DMASTER_IS_ON_RIGHT
else
    ifneq ($(MASTER),left)
$(error MASTER does not have a valid value(left/right))
    endif
endif

KEYBOARD_PATH := keyboards/$(KEYBOARD)
KEYBOARD_C := $(KEYBOARD_PATH)/$(KEYBOARD).c

ifneq ("$(wildcard $(KEYBOARD_C))","")
    include $(KEYBOARD_PATH)/rules.mk
else
    $(error "$(KEYBOARD_C)" does not exist)
endif
OPT_DEFS += -DKEYBOARD_$(KEYBOARD)

ifneq ($(SUBPROJECT),)
    SUBPROJECT_PATH := keyboards/$(KEYBOARD)/$(SUBPROJECT)
    SUBPROJECT_C := $(SUBPROJECT_PATH)/$(SUBPROJECT).c
    ifneq ("$(wildcard $(SUBPROJECT_C))","")
        OPT_DEFS += -DSUBPROJECT_$(SUBPROJECT)
        include $(SUBPROJECT_PATH)/rules.mk
    else
        $(error "$(SUBPROJECT_PATH)/$(SUBPROJECT).c" does not exist)
    endif
endif

# We can assume a ChibiOS target When MCU_FAMILY is defined, since it's not used for LUFA
ifdef MCU_FAMILY
    PLATFORM=CHIBIOS
else
    PLATFORM=AVR
endif

ifeq ($(PLATFORM),CHIBIOS)
    include $(TMK_PATH)/protocol/chibios.mk
    include $(TMK_PATH)/chibios.mk
    OPT_OS = chibios
    ifneq ("$(wildcard $(SUBPROJECT_PATH)/bootloader_defs.h)","")
        OPT_DEFS += -include $(SUBPROJECT_PATH)/bootloader_defs.h
    else ifneq ("$(wildcard $(SUBPROJECT_PATH)/boards/$(BOARD)/bootloader_defs.h)","")
        OPT_DEFS += -include $(SUBPROJECT_PATH)/boards/$(BOARD)/bootloader_defs.h
    else ifneq ("$(wildcard $(KEYBOARD_PATH)/bootloader_defs.h)","")
        OPT_DEFS += -include $(KEYBOARD_PATH)/bootloader_defs.h
    else ifneq ("$(wildcard $(KEYBOARD_PATH)/boards/$(BOARD)/bootloader_defs.h)","")
        OPT_DEFS += -include $(KEYBOARD_PATH)/boards/$(BOARD)/bootloader_defs.h
    endif
endif

CONFIG_H = $(KEYBOARD_PATH)/config.h
ifneq ($(SUBPROJECT),)
    ifneq ("$(wildcard $(SUBPROJECT_C))","")
        CONFIG_H = $(SUBPROJECT_PATH)/config.h
    endif
endif

# Save the defines and includes here, so we don't include any keymap specific ones
PROJECT_DEFS := $(OPT_DEFS)
PROJECT_INC := $(VPATH) $(EXTRAINCDIRS) $(SUBPROJECT_PATH) $(KEYBOARD_PATH)
PROJECT_CONFIG := $(CONFIG_H)

MAIN_KEYMAP_PATH := $(KEYBOARD_PATH)/keymaps/$(KEYMAP)
MAIN_KEYMAP_C := $(MAIN_KEYMAP_PATH)/keymap.c
SUBPROJ_KEYMAP_PATH := $(SUBPROJECT_PATH)/keymaps/$(KEYMAP)
SUBPROJ_KEYMAP_C := $(SUBPROJ_KEYMAP_PATH)/keymap.c
ifneq ("$(wildcard $(SUBPROJ_KEYMAP_C))","")
    -include $(SUBPROJ_KEYMAP_PATH)/rules.mk
    KEYMAP_C := $(SUBPROJ_KEYMAP_C)
    KEYMAP_PATH := $(SUBPROJ_KEYMAP_PATH)
else ifneq ("$(wildcard $(MAIN_KEYMAP_C))","")
    -include $(MAIN_KEYMAP_PATH)/rules.mk
    KEYMAP_C := $(MAIN_KEYMAP_C)
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH)
else ifneq ($(LAYOUTS),)
    include build_layout.mk
else
    $(error Could not find keymap)
    # this state should never be reached
endif

# Object files directory
#     To put object files in current directory, use a dot (.), do NOT make
#     this an empty or blank macro!
KEYMAP_OUTPUT := $(BUILD_DIR)/obj_$(TARGET)


ifneq ("$(wildcard $(KEYMAP_PATH)/config.h)","")
    CONFIG_H = $(KEYMAP_PATH)/config.h
endif

# # project specific files
SRC += $(KEYBOARD_C) \
    $(KEYMAP_C) \
    $(QUANTUM_SRC)

ifneq ($(SUBPROJECT),)
    SRC += $(SUBPROJECT_C)
endif

# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax

# Search Path
VPATH += $(KEYMAP_PATH)
ifneq ($(SUBPROJECT),)
    VPATH += $(SUBPROJECT_PATH)
endif
VPATH += $(KEYBOARD_PATH)
VPATH += $(COMMON_VPATH)

include common_features.mk
include $(TMK_PATH)/protocol.mk
include $(TMK_PATH)/common.mk

SRC += $(TMK_COMMON_SRC)
OPT_DEFS += $(TMK_COMMON_DEFS)
EXTRALDFLAGS += $(TMK_COMMON_LDFLAGS)

ifeq ($(PLATFORM),AVR)
ifeq ($(strip $(PROTOCOL)), VUSB)
    include $(TMK_PATH)/protocol/vusb.mk
else
    include $(TMK_PATH)/protocol/lufa.mk
endif
    include $(TMK_PATH)/avr.mk
endif

ifeq ($(strip $(VISUALIZER_ENABLE)), yes)
    VISUALIZER_DIR = $(QUANTUM_DIR)/visualizer
    VISUALIZER_PATH = $(QUANTUM_PATH)/visualizer
    include $(VISUALIZER_PATH)/visualizer.mk
endif

OUTPUTS := $(KEYMAP_OUTPUT) $(KEYBOARD_OUTPUT)
$(KEYMAP_OUTPUT)_SRC := $(SRC)
$(KEYMAP_OUTPUT)_DEFS := $(OPT_DEFS) $(GFXDEFS) \
-DQMK_KEYBOARD=\"$(KEYBOARD)\" -DQMK_KEYBOARD_H=\"$(KEYBOARD).h\" -DQMK_KEYBOARD_CONFIG_H=\"$(KEYBOARD_PATH)/config.h\" \
-DQMK_KEYMAP=\"$(KEYMAP)\" -DQMK_KEYMAP_H=\"$(KEYMAP).h\" -DQMK_KEYMAP_CONFIG_H=\"$(KEYMAP_PATH)/config.h\" \
-DQMK_SUBPROJECT=\"$(SUBPROJECT)\" -DQMK_SUBPROJECT_H=\"$(SUBPROJECT).h\" -DQMK_SUBPROJECT_CONFIG_H=\"$(SUBPROJECT_PATH)/config.h\"
$(KEYMAP_OUTPUT)_INC :=  $(VPATH) $(EXTRAINCDIRS)
$(KEYMAP_OUTPUT)_CONFIG := $(CONFIG_H)
$(KEYBOARD_OUTPUT)_SRC := $(CHIBISRC) $(GFXSRC)
$(KEYBOARD_OUTPUT)_DEFS := $(PROJECT_DEFS) $(GFXDEFS)
$(KEYBOARD_OUTPUT)_INC := $(PROJECT_INC) $(GFXINC)
$(KEYBOARD_OUTPUT)_CONFIG  := $(PROJECT_CONFIG)

# Default target.
all: build sizeafter

# Change the build target to build a HEX file or a library.
build: elf hex
#build: elf hex eep lss sym
#build: lib


include $(TMK_PATH)/rules.mk
