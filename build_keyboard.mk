# Determine what keyboard we are building and setup the build environment.
#
# We support folders up to 5 levels deep below `keyboards/`. This file is
# responsible for determining which folder is being used and doing the
# corresponding environment setup.

ifndef VERBOSE
.SILENT:
endif

.DEFAULT_GOAL := all

include common.mk

# Set the filename for the final firmware binary
KEYBOARD_FILESAFE := $(subst /,_,$(KEYBOARD))
TARGET ?= $(KEYBOARD_FILESAFE)_$(KEYMAP)
KEYBOARD_OUTPUT := $(BUILD_DIR)/obj_$(KEYBOARD_FILESAFE)
STM32_PATH := quantum/stm32

# Force expansion
TARGET := $(TARGET)

# For split boards we need to set a master half.
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

ifdef SKIP_VERSION
    OPT_DEFS += -DSKIP_VERSION
endif

# Determine which subfolders exist.
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
KEYBOARD_PATHS :=
KEYBOARD_PATH_1 := keyboards/$(KEYBOARD_FOLDER_PATH_1)
KEYBOARD_PATH_2 := keyboards/$(KEYBOARD_FOLDER_PATH_2)
KEYBOARD_PATH_3 := keyboards/$(KEYBOARD_FOLDER_PATH_3)
KEYBOARD_PATH_4 := keyboards/$(KEYBOARD_FOLDER_PATH_4)
KEYBOARD_PATH_5 := keyboards/$(KEYBOARD_FOLDER_PATH_5)

ifneq ("$(wildcard $(KEYBOARD_PATH_5)/)","")
    KEYBOARD_PATHS += $(KEYBOARD_PATH_5)
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_4)/)","")
    KEYBOARD_PATHS += $(KEYBOARD_PATH_4)
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_3)/)","")
    KEYBOARD_PATHS += $(KEYBOARD_PATH_3)
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_2)/)","")
    KEYBOARD_PATHS += $(KEYBOARD_PATH_2)
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_1)/)","")
    KEYBOARD_PATHS += $(KEYBOARD_PATH_1)
endif


# Pull in rules.mk files from all our subfolders
ifneq ("$(wildcard $(KEYBOARD_PATH_5)/rules.mk)","")
    include $(KEYBOARD_PATH_5)/rules.mk
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_4)/rules.mk)","")
    include $(KEYBOARD_PATH_4)/rules.mk
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_3)/rules.mk)","")
    include $(KEYBOARD_PATH_3)/rules.mk
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_2)/rules.mk)","")
    include $(KEYBOARD_PATH_2)/rules.mk
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_1)/rules.mk)","")
    include $(KEYBOARD_PATH_1)/rules.mk
endif


MAIN_KEYMAP_PATH_1 := $(KEYBOARD_PATH_1)/keymaps/$(KEYMAP)
MAIN_KEYMAP_PATH_2 := $(KEYBOARD_PATH_2)/keymaps/$(KEYMAP)
MAIN_KEYMAP_PATH_3 := $(KEYBOARD_PATH_3)/keymaps/$(KEYMAP)
MAIN_KEYMAP_PATH_4 := $(KEYBOARD_PATH_4)/keymaps/$(KEYMAP)
MAIN_KEYMAP_PATH_5 := $(KEYBOARD_PATH_5)/keymaps/$(KEYMAP)

# Check for keymap.json first, so we can regenerate keymap.c
include build_json.mk

ifeq ("$(wildcard $(KEYMAP_PATH))", "")
    # Look through the possible keymap folders until we find a matching keymap.c
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
        # If we haven't found a keymap yet fall back to community layouts
        include build_layout.mk
    else
        $(error Could not find keymap)
        # this state should never be reached
    endif
endif

ifeq ($(strip $(CTPC)), yes)
  CONVERT_TO_PROTON_C=yes
endif

ifeq ($(strip $(CONVERT_TO_PROTON_C)), yes)
    TARGET := $(TARGET)_proton_c
    include $(STM32_PATH)/proton_c.mk
    OPT_DEFS += -DCONVERT_TO_PROTON_C
endif

ifneq ($(FORCE_LAYOUT),)
    TARGET := $(TARGET)_$(FORCE_LAYOUT)
endif

include quantum/mcu_selection.mk

ifdef MCU_FAMILY
    OPT_DEFS += -DQMK_STM32
    KEYBOARD_PATHS += $(STM32_PATH)
endif


# Find all the C source files to be compiled in subfolders.
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

# Generate KEYBOARD_name_subname for all levels of the keyboard folder
KEYBOARD_FILESAFE_1 := $(subst .,,$(subst /,_,$(KEYBOARD_FOLDER_PATH_1)))
KEYBOARD_FILESAFE_2 := $(subst .,,$(subst /,_,$(KEYBOARD_FOLDER_PATH_2)))
KEYBOARD_FILESAFE_3 := $(subst .,,$(subst /,_,$(KEYBOARD_FOLDER_PATH_3)))
KEYBOARD_FILESAFE_4 := $(subst .,,$(subst /,_,$(KEYBOARD_FOLDER_PATH_4)))
KEYBOARD_FILESAFE_5 := $(subst .,,$(subst /,_,$(KEYBOARD_FOLDER_PATH_5)))

ifneq ("$(wildcard $(KEYBOARD_PATH_5)/)","")
    OPT_DEFS += -DKEYBOARD_$(KEYBOARD_FILESAFE_5)
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_4)/)","")
    OPT_DEFS += -DKEYBOARD_$(KEYBOARD_FILESAFE_4)
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_3)/)","")
    OPT_DEFS += -DKEYBOARD_$(KEYBOARD_FILESAFE_3)
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_2)/)","")
    OPT_DEFS += -DKEYBOARD_$(KEYBOARD_FILESAFE_2)
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_1)/)","")
    OPT_DEFS += -DKEYBOARD_$(KEYBOARD_FILESAFE_1)
endif

# Setup the define for QMK_KEYBOARD_H. This is used inside of keymaps so
# that the same keymap may be used on multiple keyboards.
#
# We grab the most top-level include file that we can. That file should
# use #ifdef statements to include all the neccesary subfolder includes,
# as described here:
#
#    https://docs.qmk.fm/#/feature_layouts?id=tips-for-making-layouts-keyboard-agnostic
#
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

# Determine and set parameters based on the keyboard's processor family.
# We can assume a ChibiOS target When MCU_FAMILY is defined since it's
# not used for LUFA
ifdef MCU_FAMILY
    PLATFORM=CHIBIOS
    PLATFORM_KEY=chibios
    FIRMWARE_FORMAT?=bin
else ifdef ARM_ATSAM
    PLATFORM=ARM_ATSAM
    PLATFORM_KEY=arm_atsam
    FIRMWARE_FORMAT=bin
else
    PLATFORM=AVR
    PLATFORM_KEY=avr
    FIRMWARE_FORMAT?=hex
endif

# Find all of the config.h files and add them to our CONFIG_H define.
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

POST_CONFIG_H :=
ifneq ("$(wildcard $(KEYBOARD_PATH_1)/post_config.h)","")
    POST_CONFIG_H += $(KEYBOARD_PATH_1)/post_config.h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_2)/post_config.h)","")
    POST_CONFIG_H += $(KEYBOARD_PATH_2)/post_config.h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_3)/post_config.h)","")
    POST_CONFIG_H += $(KEYBOARD_PATH_3)/post_config.h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_4)/post_config.h)","")
    POST_CONFIG_H += $(KEYBOARD_PATH_4)/post_config.h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_5)/post_config.h)","")
    POST_CONFIG_H += $(KEYBOARD_PATH_5)/post_config.h
endif

# Userspace setup and definitions
ifeq ("$(USER_NAME)","")
    USER_NAME := $(KEYMAP)
endif
USER_PATH := users/$(USER_NAME)

-include $(USER_PATH)/rules.mk
ifneq ("$(wildcard $(USER_PATH)/config.h)","")
    CONFIG_H += $(USER_PATH)/config.h
endif

# Object files directory
#     To put object files in current directory, use a dot (.), do NOT make
#     this an empty or blank macro!
KEYMAP_OUTPUT := $(BUILD_DIR)/obj_$(TARGET)

ifneq ("$(wildcard $(KEYMAP_PATH)/config.h)","")
    CONFIG_H += $(KEYMAP_PATH)/config.h
endif

# project specific files
SRC += $(KEYBOARD_SRC) \
    $(KEYMAP_C) \
    $(QUANTUM_SRC)

# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax

# Search Path
VPATH += $(KEYMAP_PATH)
VPATH += $(USER_PATH)
VPATH += $(KEYBOARD_PATHS)
VPATH += $(COMMON_VPATH)

include common_features.mk
include $(TMK_PATH)/protocol.mk
include $(TMK_PATH)/common.mk
include bootloader.mk

SRC += $(patsubst %.c,%.clib,$(LIB_SRC))
SRC += $(patsubst %.c,%.clib,$(QUANTUM_LIB_SRC))
SRC += $(TMK_COMMON_SRC)
OPT_DEFS += $(TMK_COMMON_DEFS)
EXTRALDFLAGS += $(TMK_COMMON_LDFLAGS)

include $(TMK_PATH)/$(PLATFORM_KEY).mk
ifneq ($(strip $(PROTOCOL)),)
    include $(TMK_PATH)/protocol/$(strip $(shell echo $(PROTOCOL) | tr '[:upper:]' '[:lower:]')).mk
else
    include $(TMK_PATH)/protocol/$(PLATFORM_KEY).mk
endif

# TODO: remove this bodge?
PROJECT_DEFS := $(OPT_DEFS)
PROJECT_INC := $(VPATH) $(EXTRAINCDIRS) $(KEYBOARD_PATHS)
PROJECT_CONFIG := $(CONFIG_H)

ifeq ($(strip $(VISUALIZER_ENABLE)), yes)
    VISUALIZER_DIR = $(QUANTUM_DIR)/visualizer
    VISUALIZER_PATH = $(QUANTUM_PATH)/visualizer
    include $(VISUALIZER_PATH)/visualizer.mk
endif

CONFIG_H += $(POST_CONFIG_H)
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
build: elf cpfirmware
check-size: build
objs-size: build

include show_options.mk
include $(TMK_PATH)/rules.mk
