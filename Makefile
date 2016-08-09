ifndef VERBOSE
.SILENT:
endif

STARTING_MAKEFILE := $(firstword $(MAKEFILE_LIST))
ROOT_MAKEFILE := $(lastword $(MAKEFILE_LIST))
ROOT_DIR := $(dir $(ROOT_MAKEFILE))
ifeq ($(ROOT_DIR),)
    ROOT_DIR := .
endif
ABS_STARTING_MAKEFILE := $(abspath $(STARTING_MAKEFILE))
ABS_ROOT_MAKEFILE := $(abspath $(ROOT_MAKEFILE))
ABS_STARTING_DIR := $(dir $(ABS_STARTING_MAKEFILE))
ABS_ROOT_DIR := $(dir $(ABS_ROOT_MAKEFILE))
STARTING_DIR := $(subst $(ABS_ROOT_DIR),,$(ABS_STARTING_DIR))

PATH_ELEMENTS := $(subst /, ,$(STARTING_DIR))

MAKEFILE_INCLUDED=yes

define NEXT_PATH_ELEMENT
    $$(eval CURRENT_PATH_ELEMENT := $$(firstword  $$(PATH_ELEMENTS)))
    $$(eval PATH_ELEMENTS := $$(wordlist  2,9999,$$(PATH_ELEMENTS)))
endef

$(eval $(call NEXT_PATH_ELEMENT))

ifeq ($(CURRENT_PATH_ELEMENT),keyboards)
    $(eval $(call NEXT_PATH_ELEMENT))
    KEYBOARD := $(CURRENT_PATH_ELEMENT)
    $(eval $(call NEXT_PATH_ELEMENT))
    ifeq ($(CURRENT_PATH_ELEMENT),keymaps)
        $(eval $(call NEXT_PATH_ELEMENT))
        KEYMAP := $(CURRENT_PATH_ELEMENT)
    else ifneq ($(CURRENT_PATH_ELEMENT),)
        SUBPROJECT := $(CURRENT_PATH_ELEMENT)
        $(eval $(call NEXT_PATH_ELEMENT))
        ifeq ($(CURRENT_PATH_ELEMENT),keymaps)
            $(eval $(call NEXT_PATH_ELEMENT))
            KEYMAP := $(CURRENT_PATH_ELEMENT)
        endif
    endif
endif

# Only consider folders with makefiles, to prevent errors in case there are extra folders
KEYBOARDS := $(notdir $(patsubst %/Makefile,%,$(wildcard $(ROOT_DIR)/keyboards/*/Makefile)))

#Compability with the old make variables
ifdef keyboard
    KEYBOARD := $(keyboard)
endif
ifdef sub
    SUBPROJECT := $(sub)
endif
ifdef subproject
    SUBPROJECT := $(subproject)
endif
ifdef keymap
    KEYMAP := $(keymap)
endif

$(info Keyboard: $(KEYBOARD))
$(info Keymap: $(KEYMAP))
$(info Subproject: $(SUBPROJECT))
$(info Keyboards: $(KEYBOARDS))

.DEFAULT_GOAL := all
ifneq ($(KEYMAP),)
    ifeq ($(SUBPROJECT),)
        .DEFAULT_GOAL := $(KEYBOARD)-$(KEYMAP)
    else
        .DEFAULT_GOAL := $(KEYBOARD)-$(SUBPROJECT)-$(KEYMAP)
    endif
else ifneq ($(SUBPROJECT),)
    .DEFAULT_GOAL := $(KEYBOARD)-$(SUBPROJECT)-allkm
else ifneq ($(KEYBOARD),)
    .DEFAULT_GOAL := $(KEYBOARD)-allsp-allkm
endif


# Compare the start of the RULE_VARIABLE with the first argument($1)
# If the rules equals $1 or starts with $1-, RULE_FOUND is set to true
#     and $1 is removed from the RULE variable
# Otherwise the RULE_FOUND variable is set to false
# The function is a bit tricky, since there's no built in $(startswith) function
define COMPARE_AND_REMOVE_FROM_RULE_HELPER
    ifeq ($1,$$(RULE))
        RULE:=
        RULE_FOUND := true
    else
        STARTDASH_REMOVED=$$(subst START$1-,,START$$(RULE))
        ifneq ($$(STARTDASH_REMOVED),START$$(RULE))
            RULE_FOUND := true
            RULE := $$(STARTDASH_REMOVED)
        else
            RULE_FOUND := false
        endif
    endif
endef

COMPARE_AND_REMOVE_FROM_RULE = $(eval $(call COMPARE_AND_REMOVE_FROM_RULE_HELPER,$1))$(RULE_FOUND)


# Recursively try to find a match
# $1 The list to be checked
# If a match is found, then RULE_FOUND is set to true
# and MATCHED_ITEM to the item that was matched
define TRY_TO_MATCH_RULE_FROM_LIST_HELPER
    ifneq ($1,)
        ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,$$(firstword $1)),true)
            MATCHED_ITEM := $$(firstword $1)
        else 
            $$(eval $$(call TRY_TO_MATCH_RULE_FROM_LIST_HELPER,$$(wordlist 2,9999,$1)))
        endif
    endif
endef

TRY_TO_MATCH_RULE_FROM_LIST = $(eval $(call TRY_TO_MATCH_RULE_FROM_LIST_HELPER,$1))$(RULE_FOUND)

define ALL_IN_LIST_LOOP
    OLD_RULE$1 := $$(RULE)
    $$(eval $$(call $1,$$(ITEM$1)))
    RULE := $$(OLD_RULE$1)
endef

define PARSE_ALL_IN_LIST
    $$(foreach ITEM$1,$2,$$(eval $$(call ALL_IN_LIST_LOOP,$1)))
endef

define PARSE_RULE
    RULE := $1
    COMMANDS :=
    ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,allkb),true)
        $$(eval $$(call PARSE_ALL_KEYBOARDS))
    else ifeq ($$(call TRY_TO_MATCH_RULE_FROM_LIST,$$(KEYBOARDS)),true)
        $$(eval $$(call PARSE_KEYBOARD,$$(MATCHED_ITEM)))
    else ifneq ($$(KEYBOARD),)
        $$(eval $$(call PARSE_KEYBOARD,$$(KEYBOARD)))
    else
        $$(info make: *** No rule to make target '$1'. Stop.)
		exit 1
    endif
endef

# $1 = Keyboard
define PARSE_KEYBOARD
    CURRENT_KB := $1
    # A subproject is any keyboard subfolder with a makefile
    SUBPROJECTS := $$(notdir $$(patsubst %/Makefile,%,$$(wildcard $(ROOT_DIR)/keyboards/$$(CURRENT_KB)/*/Makefile)))
    ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,allsp),true)
        $$(eval $$(call PARSE_ALL_SUBPROJECTS))
    else ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,defaultsp),true)
        $$(eval $$(call PARSE_SUBPROJECT,defaultsp))
    else ifeq ($$(call TRY_TO_MATCH_RULE_FROM_LIST,$$(SUBPROJECTS)),true)
        $$(eval $$(call PARSE_SUBPROJECT,$$(MATCHED_ITEM)))
    else ifneq ($$(SUBPROJECT),)
        $$(eval $$(call PARSE_SUBPROJECT,$$(SUBPROJECT)))
    else 
        # If there's no matching subproject, we assume it's the default
        # This will allow you to leave the subproject part of the target out
        $$(eval $$(call PARSE_SUBPROJECT,defaultsp))
    endif
endef

define PARSE_ALL_KEYBOARDS
    $$(eval $$(call PARSE_ALL_IN_LIST,PARSE_KEYBOARD,$(KEYBOARDS)))
endef

# $1 Subproject
define PARSE_SUBPROJECT
    ifeq ($1,defaultsp)
        SUBPROJECT_DEFAULT=
        $$(eval include $(ROOT_DIR)/keyboards/$$(CURRENT_KB)/Makefile)
        CURRENT_SP := $$(SUBPROJECT_DEFAULT)
    else
        CURRENT_SP := $1
    endif
    # If current subproject is empty (the default was not defined), and we have a list of subproject
    # then make all
    ifeq ($$(CURRENT_SP),)
        ifneq ($$(SUBPROJECTS),)
            CURRENT_SP := allsp
         endif
    endif
    ifneq ($$(CURRENT_SP),allsp) 
        KEYMAPS := $$(notdir $$(patsubst %/.,%,$$(wildcard $(ROOT_DIR)/keyboards/$$(CURRENT_KB)/keymaps/*/.)))
        ifneq ($$(CURRENT_SP),)
            SP_KEYMAPS := $$(notdir $$(patsubst %/.,%,$$(wildcard $(ROOT_DIR)/keyboards/$$(CURRENT_KB)/$$(CURRENT_SP)/keymaps/*/.)))
            KEYMAPS := $$(sort $$(KEYMAPS) $$(SP_KEYMAPS))
        endif
        ifeq ($$(RULE),)
            $$(eval $$(call PARSE_ALL_KEYMAPS))
        else ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,allkm),true)
            $$(eval $$(call PARSE_ALL_KEYMAPS))
        else ifeq ($$(call TRY_TO_MATCH_RULE_FROM_LIST,$$(KEYMAPS)),true)
            $$(eval $$(call PARSE_KEYMAP,$$(MATCHED_ITEM)))
        else ifneq ($$(KEYMAP),)
            $$(eval $$(call PARSE_KEYMAP,$$(KEYMAP)))
        else
            ifeq ($$(CURRENT_SP),)
                $$(info make: *** No rule to make target '$$(CURRENT_KB)-$$(RULE)'. Stop.)
            else
                $$(info make: *** No rule to make target '$$(CURRENT_KB)-$$(CURRENT_SP)-$$(RULE)'. Stop.)
            endif
			exit 1
        endif
    else
        $$(eval $$(call PARSE_ALL_IN_LIST,PARSE_SUBPROJECT,$(SUBPROJECTS)))
    endif
endef

define PARSE_ALL_SUBPROJECTS
    ifeq ($$(SUBPROJECTS),)
        $$(eval $$(call PARSE_SUBPROJECT,defaultsp))
    else
        $$(eval $$(call PARSE_ALL_IN_LIST,PARSE_SUBPROJECT,$$(SUBPROJECTS)))
    endif
endef

# $1 Keymap
define PARSE_KEYMAP
    CURRENT_KM = $1
    COMMAND := COMMAND_KEYBOARD_$$(CURRENT_KB)_SUBPROJECT_$(CURRENT_SP)_KEYMAP_$$(CURRENT_KM)
    COMMANDS += $$(COMMAND)
    ifeq ($$(CURRENT_SP),)
        KB_SP := $(CURRENT_KB)
    else
        KB_SP := $(CURRENT_KB)/$$(CURRENT_SP)
    endif
    KB_SP := $(BOLD)$$(KB_SP)$(NO_COLOR)
    MAKE_VARS := KEYBOARD=$$(CURRENT_KB) SUBPROJECT=$$(CURRENT_SP) KEYMAP=$$(CURRENT_KM)
    MAKE_VARS += VERBOSE=$(VERBOSE) COLOR=$(COLOR) SILENT=false
    COMMAND_$$(COMMAND) := \
        printf "Compiling $$(KB_SP) with $(BOLD)$$(CURRENT_KM)$(NO_COLOR)" | \
        $(AWK) '{ printf "%-118s", $$$$0;}'; \
        LOG=$$$$($$(MAKE) -r -R -C $(ROOT_DIR) -f build_keyboard.mk $$(MAKE_VARS) 2>&1) ; \
        if [ $$$$? -gt 0 ]; \
            then $$(PRINT_ERROR_PLAIN); \
        elif [ "$$$$LOG" != "" ] ; \
            then $$(PRINT_WARNING_PLAIN); \
        else \
            $$(PRINT_OK); \
        fi;
endef

define PARSE_ALL_KEYMAPS
    $$(eval $$(call PARSE_ALL_IN_LIST,PARSE_KEYMAP,$$(KEYMAPS)))
endef

include $(ROOT_DIR)/message.mk

#RUN_COMMAND = echo "Running": $(COMMAND_$(COMMAND));
RUN_COMMAND = \
$(COMMAND_$(COMMAND))
#LOG=$$(echo $(COMMAND) VERBOSE=$(VERBOSE) COLOR=$(COLOR) SILENT=true 2>&1) ; if [ $$? -gt 0 ]; then $(PRINT_ERROR_PLAIN); elif [ "$$LOG" != "" ] ; then $(PRINT_WARNING_PLAIN); else $(PRINT_OK); fi; \

# Allow specifying just the subproject, in the keyboard directory, which will compile all keymaps
SUBPROJECTS := $(notdir $(patsubst %/Makefile,%,$(wildcard ./*/Makefile)))
.PHONY: $(SUBPROJECTS)
$(SUBPROJECTS): %: %-allkm 

.PHONY: %
%: 
	cmp --version >/dev/null 2>&1; if [ $$? -gt 0 ]; then printf "$(MSG_NO_CMP)"; exit 1; fi;
	git submodule status --recursive 2>/dev/null | \
	while IFS= read -r x; do \
		case "$$x" in \
			\ *) ;; \
			*) printf "$(MSG_SUBMODULE_DIRTY)";break;; \
		esac \
	done
	$(eval $(call PARSE_RULE,$@))
	+$(foreach COMMAND,$(COMMANDS),$(RUN_COMMAND))
	

.PHONY: all
all: all-keyboards 

.PHONY: all-keyboards
all-keyboards: allkb-allsp-allkm

.PHONY: all-keyboards-defaults
all-keyboards-defaults: allkb-allsp-default


GIT_VERSION := $(shell git describe --abbrev=6 --dirty --always --tags 2>/dev/null || date +"%Y-%m-%d-%H:%M:%S")
BUILD_DATE := $(shell date +"%Y-%m-%d-%H:%M:%S")
$(shell echo '#define QMK_VERSION "$(GIT_VERSION)"' > $(ROOT_DIR)/quantum/version.h)
$(shell echo '#define QMK_BUILDDATE "$(BUILD_DATE)"' >> $(ROOT_DIR)/quantum/version.h)