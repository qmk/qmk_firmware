# Determine what keyboard we are building and setup the build environment.
#
# We support folders up to 5 levels deep below `keyboards/`. This file is
# responsible for determining which folder is being used and doing the
# corresponding environment setup.

ifndef VERBOSE
.SILENT:
endif

.DEFAULT_GOAL := all

include paths.mk
include $(BUILDDEFS_PATH)/message.mk

# Helper to add defines with a 'QMK_' prefix
define add_qmk_prefix_defs
    ifdef $1
        # Need to cater for 'STM32L4xx+'
        OPT_DEFS += -DQMK_$(2)="$($1)" -DQMK_$(2)_$(shell echo $($1) | sed -e 's@+@Plus@g' -e 's@[^a-zA-Z0-9]@_@g' | tr '[:lower:]' '[:upper:]')
    endif
endef

# Set the qmk cli to use
QMK_BIN ?= qmk

# Set the filename for the final firmware binary
KEYBOARD_FILESAFE := $(subst /,_,$(KEYBOARD))
TARGET ?= $(KEYBOARD_FILESAFE)_$(KEYMAP)

ifeq ($(strip $(DUMP_CI_METADATA)),yes)
    $(info CI Metadata: KEYBOARD=$(KEYBOARD))
    $(info CI Metadata: KEYMAP=$(KEYMAP))
endif

# Force expansion
TARGET := $(TARGET)

ifneq ($(FORCE_LAYOUT),)
    TARGET := $(TARGET)_$(FORCE_LAYOUT)
endif

# Object files and generated keymap directory
#     To put object files in current directory, use a dot (.), do NOT make
#     this an empty or blank macro!
INTERMEDIATE_OUTPUT := $(BUILD_DIR)/obj_$(TARGET)

ifdef SKIP_VERSION
    OPT_DEFS += -DSKIP_VERSION
endif

# Generate the version.h file
VERSION_H_FLAGS :=
ifdef SKIP_VERSION
VERSION_H_FLAGS += --skip-all
endif
ifdef SKIP_GIT
VERSION_H_FLAGS += --skip-git
endif

# Generate the board's version.h file.
$(shell $(QMK_BIN) generate-version-h $(VERSION_H_FLAGS) -q -o $(INTERMEDIATE_OUTPUT)/src/version.h)

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

# Pull in rules from info.json
INFO_RULES_MK = $(shell $(QMK_BIN) generate-rules-mk --quiet --escape --keyboard $(KEYBOARD) --output $(INTERMEDIATE_OUTPUT)/src/info_rules.mk)
include $(INFO_RULES_MK)

# Check for keymap.json first, so we can regenerate keymap.c
include $(BUILDDEFS_PATH)/build_json.mk

# Pull in keymap level rules.mk
ifeq ("$(wildcard $(KEYMAP_PATH))", "")
    # Look through the possible keymap folders until we find a matching keymap.c
    ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_1)/keymap.c)","")
        -include $(MAIN_KEYMAP_PATH_1)/rules.mk
        KEYMAP_C := $(MAIN_KEYMAP_PATH_1)/keymap.c
        KEYMAP_PATH := $(MAIN_KEYMAP_PATH_1)
    else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_2)/keymap.c)","")
        -include $(MAIN_KEYMAP_PATH_2)/rules.mk
        KEYMAP_C := $(MAIN_KEYMAP_PATH_2)/keymap.c
        KEYMAP_PATH := $(MAIN_KEYMAP_PATH_2)
    else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_3)/keymap.c)","")
        -include $(MAIN_KEYMAP_PATH_3)/rules.mk
        KEYMAP_C := $(MAIN_KEYMAP_PATH_3)/keymap.c
        KEYMAP_PATH := $(MAIN_KEYMAP_PATH_3)
    else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_4)/keymap.c)","")
        -include $(MAIN_KEYMAP_PATH_4)/rules.mk
        KEYMAP_C := $(MAIN_KEYMAP_PATH_4)/keymap.c
        KEYMAP_PATH := $(MAIN_KEYMAP_PATH_4)
    else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_5)/keymap.c)","")
        -include $(MAIN_KEYMAP_PATH_5)/rules.mk
        KEYMAP_C := $(MAIN_KEYMAP_PATH_5)/keymap.c
        KEYMAP_PATH := $(MAIN_KEYMAP_PATH_5)
    else ifneq ($(LAYOUTS),)
        # If we haven't found a keymap yet fall back to community layouts
        include $(BUILDDEFS_PATH)/build_layout.mk
    else
        $(call CATASTROPHIC_ERROR,Invalid keymap,Could not find keymap)
        # this state should never be reached
    endif
endif

# Have we found a keymap.json?
ifneq ("$(wildcard $(KEYMAP_JSON))", "")
    KEYMAP_C := $(INTERMEDIATE_OUTPUT)/src/keymap.c
    KEYMAP_H := $(INTERMEDIATE_OUTPUT)/src/config.h

    # Load the keymap-level rules.mk if exists
    -include $(KEYMAP_PATH)/rules.mk

    # Load any rules.mk content from keymap.json
    INFO_RULES_MK = $(shell $(QMK_BIN) generate-rules-mk --quiet --escape --output $(INTERMEDIATE_OUTPUT)/src/rules.mk $(KEYMAP_JSON))
    include $(INFO_RULES_MK)

# Add rules to generate the keymap files - indentation here is important
$(INTERMEDIATE_OUTPUT)/src/keymap.c: $(KEYMAP_JSON)
	@$(SILENT) || printf "$(MSG_GENERATING) $@" | $(AWK_CMD)
	$(eval CMD=$(QMK_BIN) json2c --quiet --output $(KEYMAP_C) $(KEYMAP_JSON))
	@$(BUILD_CMD)

$(INTERMEDIATE_OUTPUT)/src/config.h: $(KEYMAP_JSON)
	@$(SILENT) || printf "$(MSG_GENERATING) $@" | $(AWK_CMD)
	$(eval CMD=$(QMK_BIN) generate-config-h --quiet --output $(KEYMAP_H) $(KEYMAP_JSON))
	@$(BUILD_CMD)

generated-files: $(INTERMEDIATE_OUTPUT)/src/config.h $(INTERMEDIATE_OUTPUT)/src/keymap.c

endif

include $(BUILDDEFS_PATH)/converters.mk

MCU_ORIG := $(MCU)
include $(wildcard $(PLATFORM_PATH)/*/mcu_selection.mk)

# PLATFORM_KEY should be detected in info.json via key 'processor' (or rules.mk 'MCU')
ifeq ($(PLATFORM_KEY),)
    $(call CATASTROPHIC_ERROR,Platform not defined)
endif
PLATFORM=$(shell echo $(PLATFORM_KEY) | tr '[:lower:]' '[:upper:]')

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
# use #ifdef statements to include all the necessary subfolder includes,
# as described here:
#
#    https://docs.qmk.fm/#/feature_layouts?id=tips-for-making-layouts-keyboard-agnostic
#
ifneq ("$(wildcard $(KEYBOARD_PATH_1)/$(KEYBOARD_FOLDER_1).h)","")
    FOUND_KEYBOARD_H = $(KEYBOARD_FOLDER_1).h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_2)/$(KEYBOARD_FOLDER_2).h)","")
    FOUND_KEYBOARD_H = $(KEYBOARD_FOLDER_2).h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_3)/$(KEYBOARD_FOLDER_3).h)","")
    FOUND_KEYBOARD_H = $(KEYBOARD_FOLDER_3).h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_4)/$(KEYBOARD_FOLDER_4).h)","")
    FOUND_KEYBOARD_H = $(KEYBOARD_FOLDER_4).h
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_5)/$(KEYBOARD_FOLDER_5).h)","")
    FOUND_KEYBOARD_H = $(KEYBOARD_FOLDER_5).h
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

# Pull in stuff from info.json
INFO_JSON_FILES :=
ifneq ("$(wildcard $(KEYBOARD_PATH_1)/info.json)","")
    INFO_JSON_FILES += $(KEYBOARD_PATH_1)/info.json
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_2)/info.json)","")
    INFO_JSON_FILES += $(KEYBOARD_PATH_2)/info.json
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_3)/info.json)","")
    INFO_JSON_FILES += $(KEYBOARD_PATH_3)/info.json
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_4)/info.json)","")
    INFO_JSON_FILES += $(KEYBOARD_PATH_4)/info.json
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_5)/info.json)","")
    INFO_JSON_FILES += $(KEYBOARD_PATH_5)/info.json
endif

CONFIG_H += $(INTERMEDIATE_OUTPUT)/src/info_config.h
KEYBOARD_SRC += $(INTERMEDIATE_OUTPUT)/src/default_keyboard.c

$(INTERMEDIATE_OUTPUT)/src/info_config.h: $(INFO_JSON_FILES)
	@$(SILENT) || printf "$(MSG_GENERATING) $@" | $(AWK_CMD)
	$(eval CMD=$(QMK_BIN) generate-config-h --quiet --keyboard $(KEYBOARD) --output $(INTERMEDIATE_OUTPUT)/src/info_config.h)
	@$(BUILD_CMD)

$(INTERMEDIATE_OUTPUT)/src/default_keyboard.c: $(INFO_JSON_FILES)
	@$(SILENT) || printf "$(MSG_GENERATING) $@" | $(AWK_CMD)
	$(eval CMD=$(QMK_BIN) generate-keyboard-c --quiet --keyboard $(KEYBOARD) --output $(INTERMEDIATE_OUTPUT)/src/default_keyboard.c)
	@$(BUILD_CMD)

$(INTERMEDIATE_OUTPUT)/src/default_keyboard.h: $(INFO_JSON_FILES)
	@$(SILENT) || printf "$(MSG_GENERATING) $@" | $(AWK_CMD)
	$(eval CMD=$(QMK_BIN) generate-keyboard-h --quiet --keyboard $(KEYBOARD) --include $(FOUND_KEYBOARD_H) --output $(INTERMEDIATE_OUTPUT)/src/default_keyboard.h)
	@$(BUILD_CMD)

generated-files: $(INTERMEDIATE_OUTPUT)/src/info_config.h $(INTERMEDIATE_OUTPUT)/src/default_keyboard.c $(INTERMEDIATE_OUTPUT)/src/default_keyboard.h

generated-files: $(INTERMEDIATE_OUTPUT)/src/info_deps.d

$(INTERMEDIATE_OUTPUT)/src/info_deps.d:
	@$(SILENT) || printf "$(MSG_GENERATING) $@" | $(AWK_CMD)
	$(eval CMD=$(QMK_BIN) generate-make-dependencies -kb $(KEYBOARD) -km $(KEYMAP) -o $(INTERMEDIATE_OUTPUT)/src/info_deps.d)
	@$(BUILD_CMD)

-include $(INTERMEDIATE_OUTPUT)/src/info_deps.d

.INTERMEDIATE : generated-files

# Userspace setup and definitions
ifeq ("$(USER_NAME)","")
    USER_NAME := $(KEYMAP)
endif
USER_PATH := users/$(USER_NAME)

# Pull in user level rules.mk
-include $(USER_PATH)/rules.mk
ifneq ("$(wildcard $(USER_PATH)/config.h)","")
    CONFIG_H += $(USER_PATH)/config.h
endif
ifneq ("$(wildcard $(USER_PATH)/post_config.h)","")
    POST_CONFIG_H += $(USER_PATH)/post_config.h
endif

# Disable features that a keyboard doesn't support
-include $(BUILDDEFS_PATH)/disable_features.mk

ifneq ("$(CONVERTER)","")
    -include $(CONVERTER)/post_converter.mk
endif

# Pull in post_rules.mk files from all our subfolders
ifneq ("$(wildcard $(KEYBOARD_PATH_1)/post_rules.mk)","")
    include $(KEYBOARD_PATH_1)/post_rules.mk
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_2)/post_rules.mk)","")
    include $(KEYBOARD_PATH_2)/post_rules.mk
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_3)/post_rules.mk)","")
    include $(KEYBOARD_PATH_3)/post_rules.mk
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_4)/post_rules.mk)","")
    include $(KEYBOARD_PATH_4)/post_rules.mk
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_5)/post_rules.mk)","")
    include $(KEYBOARD_PATH_5)/post_rules.mk
endif

ifneq ("$(wildcard $(KEYMAP_PATH)/config.h)","")
    CONFIG_H += $(KEYMAP_PATH)/config.h
endif
ifneq ("$(KEYMAP_H)","")
    CONFIG_H += $(KEYMAP_H)
endif

OPT_DEFS += -DKEYMAP_C=\"$(KEYMAP_C)\"

# If a keymap or userspace places their keymap array in another file instead, allow for it to be included
# !!NOTE!! -- For this to work, the source file cannot be part of $(SRC), so users should not add it via `SRC += <file>`
ifneq ($(strip $(INTROSPECTION_KEYMAP_C)),)
OPT_DEFS += -DINTROSPECTION_KEYMAP_C=\"$(strip $(INTROSPECTION_KEYMAP_C))\"
endif

# project specific files
SRC += \
    $(KEYBOARD_SRC) \
    $(QUANTUM_DIR)/keymap_introspection.c \
    $(QUANTUM_SRC) \
    $(QUANTUM_DIR)/main.c \

# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax

# Search Path
VPATH += $(KEYMAP_PATH)
VPATH += $(USER_PATH)
VPATH += $(KEYBOARD_PATHS)
VPATH += $(COMMON_VPATH)
VPATH += $(INTERMEDIATE_OUTPUT)/src

include $(BUILDDEFS_PATH)/common_features.mk
include $(BUILDDEFS_PATH)/generic_features.mk
include $(TMK_PATH)/protocol.mk
include $(PLATFORM_PATH)/common.mk

SRC += $(patsubst %.c,%.clib,$(LIB_SRC))
SRC += $(patsubst %.c,%.clib,$(QUANTUM_LIB_SRC))

-include $(PLATFORM_PATH)/$(PLATFORM_KEY)/bootloader.mk
include $(PLATFORM_PATH)/$(PLATFORM_KEY)/platform.mk
-include $(PLATFORM_PATH)/$(PLATFORM_KEY)/flash.mk

ifneq ($(strip $(PROTOCOL)),)
PROTOCOL_KEY = $(strip $(shell echo $(PROTOCOL) | tr '[:upper:]' '[:lower:]'))
else
PROTOCOL_KEY = $(PLATFORM_KEY)
endif
include $(TMK_PATH)/protocol/$(PROTOCOL_KEY)/$(PROTOCOL_KEY).mk

# Setup definitions based on the selected MCU
$(eval $(call add_qmk_prefix_defs,MCU_ORIG,MCU))
$(eval $(call add_qmk_prefix_defs,MCU_ARCH,MCU_ARCH))
$(eval $(call add_qmk_prefix_defs,MCU_PORT_NAME,MCU_PORT_NAME))
$(eval $(call add_qmk_prefix_defs,MCU_FAMILY,MCU_FAMILY))
$(eval $(call add_qmk_prefix_defs,MCU_SERIES,MCU_SERIES))
$(eval $(call add_qmk_prefix_defs,BOARD,BOARD))

# Control whether intermediate file listings are generated
# e.g.:
#    make handwired/onekey/blackpill_f411:default KEEP_INTERMEDIATES=yes
#    cat .build/obj_handwired_onekey_blackpill_f411_default/quantum/quantum.i | sed -e 's@^#.*@@g' -e 's@^\s*//.*@@g' -e '/^\s*$/d' | clang-format
ifeq ($(strip $(KEEP_INTERMEDIATES)), yes)
    OPT_DEFS += -save-temps=obj
endif

# TODO: remove this bodge?
PROJECT_DEFS := $(OPT_DEFS)
PROJECT_INC := $(VPATH) $(EXTRAINCDIRS) $(KEYBOARD_PATHS)
PROJECT_CONFIG := $(CONFIG_H)

CONFIG_H += $(POST_CONFIG_H)
ALL_CONFIGS := $(PROJECT_CONFIG) $(CONFIG_H)

OUTPUTS := $(INTERMEDIATE_OUTPUT)
$(INTERMEDIATE_OUTPUT)_SRC := $(SRC) $(PLATFORM_SRC)
$(INTERMEDIATE_OUTPUT)_DEFS := $(OPT_DEFS) \
	-DQMK_KEYBOARD=\"$(KEYBOARD)\" -DQMK_KEYBOARD_H=\"$(INTERMEDIATE_OUTPUT)/src/default_keyboard.h\" \
	-DQMK_KEYMAP=\"$(KEYMAP)\" -DQMK_KEYMAP_H=\"$(KEYMAP).h\" -DQMK_KEYMAP_CONFIG_H=\"$(KEYMAP_PATH)/config.h\" \
	$(PROJECT_DEFS)
$(INTERMEDIATE_OUTPUT)_INC :=  $(VPATH) $(EXTRAINCDIRS) $(PROJECT_INC)
$(INTERMEDIATE_OUTPUT)_CONFIG := $(CONFIG_H) $(PROJECT_CONFIG)

# Default target.
all: build check-size

build: elf cpfirmware
check-size: build
check-md5: build
objs-size: build

ifneq ($(strip $(TOP_SYMBOLS)),)
ifeq ($(strip $(TOP_SYMBOLS)),yes)
NUM_TOP_SYMBOLS := 10
else
NUM_TOP_SYMBOLS := $(strip $(TOP_SYMBOLS))
endif
all: top-symbols
check-size: top-symbols
top-symbols: build
	echo "###########################################"
	echo "# Highest flash usage:"
	$(NM) -Crtd --size-sort $(BUILD_DIR)/$(TARGET).elf | grep ' [RrTt] ' | head -n$(NUM_TOP_SYMBOLS) | sed -e 's#^0000000#       #g' -e 's#^000000#      #g' -e 's#^00000#     #g' -e 's#^0000#    #g' -e 's#^000#   #g' -e 's#^00#  #g' -e 's#^0# #g'
	echo "###########################################"
	echo "# Highest RAM usage:"
	$(NM) -Crtd --size-sort $(BUILD_DIR)/$(TARGET).elf | grep ' [BbCDdGgSs] ' | head -n$(NUM_TOP_SYMBOLS) | sed -e 's#^0000000#       #g' -e 's#^000000#      #g' -e 's#^00000#     #g' -e 's#^0000#    #g' -e 's#^000#   #g' -e 's#^00#  #g' -e 's#^0# #g'
	echo "###########################################"
endif

include $(BUILDDEFS_PATH)/show_options.mk
include $(BUILDDEFS_PATH)/common_rules.mk

# Ensure we have generated files available for each of the objects
define GEN_FILES
$1: generated-files
endef
$(foreach O,$(OBJ),$(eval $(call GEN_FILES,$(patsubst %.a,%.o,$(O)))))
