ifndef VERBOSE
.SILENT:
endif

.DEFAULT_GOAL := all

include common.mk

# 5/4/3/2/1
KEYBOARD_FOLDER_PATH_1 := $(KEYBOARD)
KEYBOARD_FOLDER_PATH_2 := $(patsubst %/,%,$(dir $(KEYBOARD_FOLDER_PATH_1)))
KEYBOARD_FOLDER_PATH_3 := $(patsubst %/,%,$(dir $(KEYBOARD_FOLDER_PATH_2)))
KEYBOARD_FOLDER_PATH_4 := $(patsubst %/,%,$(dir $(KEYBOARD_FOLDER_PATH_3)))
KEYBOARD_FOLDER_PATH_5 := $(patsubst %/,%,$(dir $(KEYBOARD_FOLDER_PATH_4)))
KEYBOARD_FOLDER_1 := $(notdir $(KEYBOARD_FOLDER_PATH_1))
KEYBOARD_FOLDER_2 := $(notdir $(KEYBOARD_FOLDER_PATH_2))
KEYBOARD_FOLDER_3 := $(notdir $(KEYBOARD_FOLDER_PATH_3))
KEYBOARD_FOLDER_4 := $(notdir $(KEYBOARD_FOLDER_PATH_4))
KEYBOARD_FOLDER_5 := $(notdir $(KEYBOARD_FOLDER_PATH_5))

KEYBOARD_FILESAFE := $(subst /,_,$(KEYBOARD))

TARGET ?= $(KEYBOARD_FILESAFE)_$(KEYMAP)
KEYBOARD_OUTPUT := $(BUILD_DIR)/obj_$(KEYBOARD_FILESAFE)

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

KEYBOARD_PATHS :=

KEYBOARD_PATH_1 := keyboards/$(KEYBOARD_FOLDER_PATH_1)
KEYBOARD_PATH_2 := keyboards/$(KEYBOARD_FOLDER_PATH_2)
KEYBOARD_PATH_3 := keyboards/$(KEYBOARD_FOLDER_PATH_3)
KEYBOARD_PATH_4 := keyboards/$(KEYBOARD_FOLDER_PATH_4)
KEYBOARD_PATH_5 := keyboards/$(KEYBOARD_FOLDER_PATH_5)

ifneq ("$(wildcard $(KEYBOARD_PATH_5)/rules.mk)","")
    KEYBOARD_PATHS += $(KEYBOARD_PATH_5)
    include $(KEYBOARD_PATH_5)/rules.mk
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_4)/rules.mk)","")
    KEYBOARD_PATHS += $(KEYBOARD_PATH_4)
    include $(KEYBOARD_PATH_4)/rules.mk
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_3)/rules.mk)","")
    KEYBOARD_PATHS += $(KEYBOARD_PATH_3)
    include $(KEYBOARD_PATH_3)/rules.mk
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_2)/rules.mk)","")
    KEYBOARD_PATHS += $(KEYBOARD_PATH_2)
    include $(KEYBOARD_PATH_2)/rules.mk
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_1)/rules.mk)","")
    KEYBOARD_PATHS += $(KEYBOARD_PATH_1)
    include $(KEYBOARD_PATH_1)/rules.mk
endif

KEYBOARD_SRC :=

KEYBOARD_C_1 := $(KEYBOARD_PATH_1)/$(KEYBOARD_FOLDER_1).c
KEYBOARD_C_2 := $(KEYBOARD_PATH_2)/$(KEYBOARD_FOLDER_2).c
KEYBOARD_C_3 := $(KEYBOARD_PATH_3)/$(KEYBOARD_FOLDER_3).c
KEYBOARD_C_4 := $(KEYBOARD_PATH_4)/$(KEYBOARD_FOLDER_4).c
KEYBOARD_C_5 := $(KEYBOARD_PATH_5)/$(KEYBOARD_FOLDER_5).c

ifneq ("$(wildcard $(KEYBOARD_C_5))","")
    KEYBOARD_SRC += $(KEYBOARD_C_5)
endif
ifneq ("$(wildcard $(KEYBOARD_C_4))","")
    KEYBOARD_SRC += $(KEYBOARD_C_4)
endif
ifneq ("$(wildcard $(KEYBOARD_C_3))","")
    KEYBOARD_SRC += $(KEYBOARD_C_3)
endif
ifneq ("$(wildcard $(KEYBOARD_C_2))","")
    KEYBOARD_SRC += $(KEYBOARD_C_2)
endif
ifneq ("$(wildcard $(KEYBOARD_C_1))","")
    KEYBOARD_SRC += $(KEYBOARD_C_1)
endif

OPT_DEFS += -DKEYBOARD_$(KEYBOARD_FILESAFE)


ifneq ("$(wildcard $(KEYBOARD_PATH_1)/$(KEYBOARD_FOLDER_1).h)","")
    QMK_KEYBOARD_H = $(KEYBOARD_FOLDER_1).h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_2)/$(KEYBOARD_FOLDER_2).h)","")
    QMK_KEYBOARD_H = $(KEYBOARD_FOLDER_2).h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_3)/$(KEYBOARD_FOLDER_3).h)","")
    QMK_KEYBOARD_H = $(KEYBOARD_FOLDER_3).h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_4)/$(KEYBOARD_FOLDER_4).h)","")
    QMK_KEYBOARD_H = $(KEYBOARD_FOLDER_4).h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_5)/$(KEYBOARD_FOLDER_5).h)","")
    QMK_KEYBOARD_H = $(KEYBOARD_FOLDER_5).h
endif

# We can assume a ChibiOS target When MCU_FAMILY is defined , since it's not used for LUFA
ifdef MCU_FAMILY
    PLATFORM=CHIBIOS
else
    PLATFORM=AVR
endif

ifeq ($(PLATFORM),CHIBIOS)
    include $(TMK_PATH)/protocol/chibios.mk
    include $(TMK_PATH)/chibios.mk
    OPT_OS = chibios
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
    endif
endif

CONFIG_H :=
ifneq ("$(wildcard $(KEYBOARD_PATH_5)/config.h)","")
    CONFIG_H += $(KEYBOARD_PATH_5)/config.h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_4)/config.h)","")
    CONFIG_H += $(KEYBOARD_PATH_4)/config.h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_3)/config.h)","")
    CONFIG_H += $(KEYBOARD_PATH_3)/config.h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_2)/config.h)","")
    CONFIG_H += $(KEYBOARD_PATH_2)/config.h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_1)/config.h)","")
    CONFIG_H += $(KEYBOARD_PATH_1)/config.h
endif

# Save the defines and includes here, so we don't include any keymap specific ones
PROJECT_DEFS := $(OPT_DEFS)
PROJECT_INC := $(VPATH) $(EXTRAINCDIRS) $(KEYBOARD_PATHS)
PROJECT_CONFIG := $(CONFIG_H)

MAIN_KEYMAP_PATH_1 := $(KEYBOARD_PATH_1)/keymaps/$(KEYMAP)
MAIN_KEYMAP_PATH_2 := $(KEYBOARD_PATH_2)/keymaps/$(KEYMAP)
MAIN_KEYMAP_PATH_3 := $(KEYBOARD_PATH_3)/keymaps/$(KEYMAP)
MAIN_KEYMAP_PATH_4 := $(KEYBOARD_PATH_4)/keymaps/$(KEYMAP)
MAIN_KEYMAP_PATH_5 := $(KEYBOARD_PATH_5)/keymaps/$(KEYMAP)

ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_5)/keymap.c)","")
    -include $(MAIN_KEYMAP_PATH_5)/rules.mk
    KEYMAP_C := $(MAIN_KEYMAP_PATH_5)/keymap.c
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH_5)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_4)/keymap.c)","")
    -include $(MAIN_KEYMAP_PATH_4)/rules.mk
    KEYMAP_C := $(MAIN_KEYMAP_PATH_4)/keymap.c
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH_4)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_3)/keymap.c)","")
    -include $(MAIN_KEYMAP_PATH_3)/rules.mk
    KEYMAP_C := $(MAIN_KEYMAP_PATH_3)/keymap.c
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH_3)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_2)/keymap.c)","")
    -include $(MAIN_KEYMAP_PATH_2)/rules.mk
    KEYMAP_C := $(MAIN_KEYMAP_PATH_2)/keymap.c
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH_2)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_1)/keymap.c)","")
    -include $(MAIN_KEYMAP_PATH_1)/rules.mk
    KEYMAP_C := $(MAIN_KEYMAP_PATH_1)/keymap.c
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH_1)
else ifneq ($(LAYOUTS),)
    include build_layout.mk
else 
    $(error Could not find keymap)
    # this state should never be reached
endif

# User space stuff
USER_PATH := users/$(KEYMAP)
-include $(USER_PATH)/rules.mk

# Object files directory
#     To put object files in current directory, use a dot (.), do NOT make
#     this an empty or blank macro!
KEYMAP_OUTPUT := $(BUILD_DIR)/obj_$(TARGET)

ifneq ("$(wildcard $(KEYMAP_PATH)/config.h)","")
    CONFIG_H += $(KEYMAP_PATH)/config.h
endif

# # project specific files
SRC += $(KEYBOARD_SRC) \
    $(KEYMAP_C) \
    $(QUANTUM_SRC)

# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax

# Search Path
VPATH += $(KEYMAP_PATH)
VPATH += $(KEYBOARD_PATHS)
VPATH += $(COMMON_VPATH)
VPATH += $(USER_PATH)

include common_features.mk
include $(TMK_PATH)/protocol.mk
include $(TMK_PATH)/common.mk
include bootloader.mk

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

ALL_CONFIGS := $(PROJECT_CONFIG) $(CONFIG_H)

OUTPUTS := $(KEYMAP_OUTPUT) $(KEYBOARD_OUTPUT)
$(KEYMAP_OUTPUT)_SRC := $(SRC)
$(KEYMAP_OUTPUT)_DEFS := $(OPT_DEFS) $(GFXDEFS) \
-DQMK_KEYBOARD=\"$(KEYBOARD)\" -DQMK_KEYBOARD_H=\"$(QMK_KEYBOARD_H)\" -DQMK_KEYBOARD_CONFIG_H=\"$(KEYBOARD_PATH_1)/config.h\" \
-DQMK_KEYMAP=\"$(KEYMAP)\" -DQMK_KEYMAP_H=\"$(KEYMAP).h\" -DQMK_KEYMAP_CONFIG_H=\"$(KEYMAP_PATH)/config.h\" \
-DQMK_SUBPROJECT -DQMK_SUBPROJECT_H -DQMK_SUBPROJECT_CONFIG_H
$(KEYMAP_OUTPUT)_INC :=  $(VPATH) $(EXTRAINCDIRS)
$(KEYMAP_OUTPUT)_CONFIG := $(CONFIG_H)
$(KEYBOARD_OUTPUT)_SRC := $(CHIBISRC) $(GFXSRC)
$(KEYBOARD_OUTPUT)_DEFS := $(PROJECT_DEFS) $(GFXDEFS)
$(KEYBOARD_OUTPUT)_INC := $(PROJECT_INC) $(GFXINC)
$(KEYBOARD_OUTPUT)_CONFIG := $(PROJECT_CONFIG)

# Default target.
all: build check-size

# Change the build target to build a HEX file or a library.
build: elf cphex
#build: elf hex eep lss sym
#build: lib


include $(TMK_PATH)/rules.mk
