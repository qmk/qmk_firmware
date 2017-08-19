ifndef VERBOSE
.SILENT:
endif

# Never run this makefile in parallel, as it could screw things up
# It won't affect the submakes, so you still get the speedup from specifying -jx
.NOTPARALLEL:

# Allow the silent with lower caps to work the same way as upper caps
ifdef silent
    SILENT = $(silent)
endif

ifdef SILENT
    SUB_IS_SILENT := $(SILENT)
endif

# We need to make sure that silent is always turned off at the top level
# Otherwise the [OK], [ERROR] and [WARN] messages won't be displayed correctly
override SILENT := false

QMK_VERSION := $(shell git describe --abbrev=0 --tags 2>/dev/null)
ifneq ($(QMK_VERSION),)
$(info QMK Firmware v$(QMK_VERSION))
endif

ON_ERROR := error_occurred=1

BREAK_ON_ERRORS = no

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
BUILD_DIR := $(ROOT_DIR)/.build
TEST_DIR := $(BUILD_DIR)/test
ERROR_FILE := $(BUILD_DIR)/error_occurred

MAKEFILE_INCLUDED=yes

# Helper function to process the newt element of a space separated path
# It works a bit like the traditional functional head tail
# so the CURRENT_PATH_ELEMENT will become the new head
# and the PATH_ELEMENTS are the rest that are still unprocessed
define NEXT_PATH_ELEMENT
    $$(eval CURRENT_PATH_ELEMENT := $$(firstword  $$(PATH_ELEMENTS)))
    $$(eval PATH_ELEMENTS := $$(wordlist  2,9999,$$(PATH_ELEMENTS)))
endef

# We change the / to spaces so that we more easily can work with the elements
# separately
PATH_ELEMENTS := $(subst /, ,$(STARTING_DIR))
# Initialize the path elements list for further processing
$(eval $(call NEXT_PATH_ELEMENT))

# This function sets the KEYBOARD; KEYMAP and SUBPROJECT to the correct
# variables depending on which directory you stand in.
# It's really a very simple if else chain, if you squint enough,
# but the makefile syntax makes it very verbose.
# If we are in a subfolder of keyboards
ifeq ($(CURRENT_PATH_ELEMENT),keyboards)
    $(eval $(call NEXT_PATH_ELEMENT))
    KEYBOARD := $(CURRENT_PATH_ELEMENT)
    $(eval $(call NEXT_PATH_ELEMENT))
    # If we are in a subfolder of keymaps, or in other words in a keymap
    # folder
    ifeq ($(CURRENT_PATH_ELEMENT),keymaps)
        $(eval $(call NEXT_PATH_ELEMENT))
        KEYMAP := $(CURRENT_PATH_ELEMENT)
     # else if we are not in the keyboard folder itself
    else ifneq ($(CURRENT_PATH_ELEMENT),)
        # the we can assume it's a subproject, as no other folders
        # should have make files in them
        SUBPROJECT := $(CURRENT_PATH_ELEMENT)
        $(eval $(call NEXT_PATH_ELEMENT))
        # if we are inside a keymap folder of a subproject
        ifeq ($(CURRENT_PATH_ELEMENT),keymaps)
            $(eval $(call NEXT_PATH_ELEMENT))
            KEYMAP := $(CURRENT_PATH_ELEMENT)
        endif
    endif
endif

# Only consider folders with makefiles, to prevent errors in case there are extra folders
KEYBOARDS := $(notdir $(patsubst %/Makefile,%,$(wildcard $(ROOT_DIR)/keyboards/*/Makefile)))

#Compatibility with the old make variables, anything you specify directly on the command line
# always overrides the detected folders
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

# Uncomment these for debugging
#$(info Keyboard: $(KEYBOARD))
#$(info Keymap: $(KEYMAP))
#$(info Subproject: $(SUBPROJECT))
#$(info Keyboards: $(KEYBOARDS))


# Set the default goal depending on where we are running make from
# this handles the case where you run make without any arguments
.DEFAULT_GOAL := all
ifneq ($(KEYMAP),)
    ifeq ($(SUBPROJECT),)
         # Inside a keymap folder, just build the keymap, with the
         # default subproject
        .DEFAULT_GOAL := $(KEYBOARD)-$(KEYMAP)
    else
         # Inside a subproject keyamp folder, build the keymap
         # for that subproject
        .DEFAULT_GOAL := $(KEYBOARD)-$(SUBPROJECT)-$(KEYMAP)
    endif
else ifneq ($(SUBPROJECT),)
     # Inside a subproject folder, build all keymaps for that subproject
    .DEFAULT_GOAL := $(KEYBOARD)-$(SUBPROJECT)-allkm
else ifneq ($(KEYBOARD),)
     # Inside a keyboard folder, build all keymaps for all subprojects
     # Note that this is different from the old behaviour, which would
     # build only the default keymap of the default keyboard
    .DEFAULT_GOAL := $(KEYBOARD)-allsp-allkm
endif


# Compare the start of the RULE variable with the first argument($1)
# If the rules equals $1 or starts with $1-, RULE_FOUND is set to true
#     and $1 is removed from the RULE variable
# Otherwise the RULE_FOUND variable is set to false, and RULE left as it was
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

# This makes it easier to call COMPARE_AND_REMOVE_FROM_RULE, since it makes it behave like
# a function that returns the value
COMPARE_AND_REMOVE_FROM_RULE = $(eval $(call COMPARE_AND_REMOVE_FROM_RULE_HELPER,$1))$(RULE_FOUND)


# Recursively try to find a match for the start of the rule to be checked
# $1 The list to be checked
# If a match is found, then RULE_FOUND is set to true
# and MATCHED_ITEM to the item that was matched
define TRY_TO_MATCH_RULE_FROM_LIST_HELPER3
    ifneq ($1,)
        ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,$$(firstword $1)),true)
            MATCHED_ITEM := $$(firstword $1)
        else
            $$(eval $$(call TRY_TO_MATCH_RULE_FROM_LIST_HELPER3,$$(wordlist 2,9999,$1)))
        endif
    endif
endef

# A recursive helper function for finding the longest match
# $1 The list to be checked
# It works by always removing the currently matched item from the list
# and call itself recursively, until a match is found
define TRY_TO_MATCH_RULE_FROM_LIST_HELPER2
    # Stop the recursion when the list is empty
    ifneq ($1,)
        RULE_BEFORE := $$(RULE)
        $$(eval $$(call TRY_TO_MATCH_RULE_FROM_LIST_HELPER3,$1))
        # If a match is found in the current list, otherwise just return what we had before
        ifeq ($$(RULE_FOUND),true)
            # Save the best match so far and call itself recursively
            BEST_MATCH := $$(MATCHED_ITEM)
            BEST_MATCH_RULE := $$(RULE)
            RULE_FOUND := false
            RULE := $$(RULE_BEFORE)
            $$(eval $$(call TRY_TO_MATCH_RULE_FROM_LIST_HELPER2,$$(filter-out $$(MATCHED_ITEM),$1)))
        endif
     endif
endef


# Recursively try to find the longest match for the start of the rule to be checked
# $1 The list to be checked
# If a match is found, then RULE_FOUND is set to true
# and MATCHED_ITEM to the item that was matched
define TRY_TO_MATCH_RULE_FROM_LIST_HELPER
    BEST_MATCH :=
    $$(eval $$(call TRY_TO_MATCH_RULE_FROM_LIST_HELPER2,$1))
    ifneq ($$(BEST_MATCH),)
        RULE_FOUND := true
        RULE := $$(BEST_MATCH_RULE)
        MATCHED_ITEM := $$(BEST_MATCH)
    else
        RULE_FOUND := false
        MATCHED_ITEM :=
    endif
endef

# Make it easier to call TRY_TO_MATCH_RULE_FROM_LIST
TRY_TO_MATCH_RULE_FROM_LIST = $(eval $(call TRY_TO_MATCH_RULE_FROM_LIST_HELPER,$1))$(RULE_FOUND)

define ALL_IN_LIST_LOOP
    OLD_RULE$1 := $$(RULE)
    $$(eval $$(call $1,$$(ITEM$1)))
    RULE := $$(OLD_RULE$1)
endef

define PARSE_ALL_IN_LIST
    $$(foreach ITEM$1,$2,$$(eval $$(call ALL_IN_LIST_LOOP,$1)))
endef

# The entry point for rule parsing
# parses a rule in the format <keyboard>-<subproject>-<keymap>-<target>
# but this particular function only deals with the first <keyboard> part
define PARSE_RULE
    RULE := $1
    COMMANDS :=
    # If the rule starts with allkb, then continue the parsing from
    # PARSE_ALL_KEYBOARDS
    ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,allkb),true)
        $$(eval $$(call PARSE_ALL_KEYBOARDS))
    else ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,test),true)
        $$(eval $$(call PARSE_TEST))
    # If the rule starts with the name of a known keyboard, then continue
    # the parsing from PARSE_KEYBOARD
    else ifeq ($$(call TRY_TO_MATCH_RULE_FROM_LIST,$$(KEYBOARDS)),true)
        $$(eval $$(call PARSE_KEYBOARD,$$(MATCHED_ITEM)))
    # Otherwise use the KEYBOARD variable, which is determined either by
    # the current directory you run make from, or passed in as an argument
    else ifneq ($$(KEYBOARD),)
        $$(eval $$(call PARSE_KEYBOARD,$$(KEYBOARD)))
    else
        $$(info make: *** No rule to make target '$1'. Stop.)
        # Notice the tab instead of spaces below!
		exit 1
    endif
endef

# $1 = Keyboard
# Parses a rule in the format <subproject>-<keymap>-<target>
# the keyboard is already known when entering this function
define PARSE_KEYBOARD
    CURRENT_KB := $1
    # A subproject is any keyboard subfolder with a makefile
    SUBPROJECTS := $$(notdir $$(patsubst %/Makefile,%,$$(wildcard $(ROOT_DIR)/keyboards/$$(CURRENT_KB)/*/Makefile)))
    # if the rule starts with allsp, then continue with looping over all subprojects
    ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,allsp),true)
        $$(eval $$(call PARSE_ALL_SUBPROJECTS))
    # A special case for matching the defaultsp (default subproject)
    else ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,defaultsp),true)
        $$(eval $$(call PARSE_SUBPROJECT,defaultsp))
    # If the rule starts with the name of a known subproject
    else ifeq ($$(call TRY_TO_MATCH_RULE_FROM_LIST,$$(SUBPROJECTS)),true)
        $$(eval $$(call PARSE_SUBPROJECT,$$(MATCHED_ITEM)))
    # Try to use the SUBPROJECT variable, which is either determined by the
    # directory which invoked make, or passed as an argument to make
    else ifneq ($$(SUBPROJECT),)
        $$(eval $$(call PARSE_SUBPROJECT,$$(SUBPROJECT)))
	# If there's no matching subproject, we assume it's the default
	# This will allow you to leave the subproject part of the target out
    else
        $$(eval $$(call PARSE_SUBPROJECT,))
    endif
endef

# if we are going to compile all keyboards, match the rest of the rule
# for each of them
define PARSE_ALL_KEYBOARDS
    $$(eval $$(call PARSE_ALL_IN_LIST,PARSE_KEYBOARD,$(KEYBOARDS)))
endef

# $1 Subproject
# When entering this, the keyboard and subproject are known, so now we need
# to determine which keymaps are going to get compiled
define PARSE_SUBPROJECT
    # If we want to compile the default subproject, then we need to
    # include the correct makefile to determine the actual name of it
    CURRENT_SP := $1
    ifeq ($$(CURRENT_SP),)
        CURRENT_SP := defaultsp
    endif
    ifeq ($$(CURRENT_SP),defaultsp)
        SUBPROJECT_DEFAULT=
        $$(eval include $(ROOT_DIR)/keyboards/$$(CURRENT_KB)/Makefile)
        CURRENT_SP := $$(SUBPROJECT_DEFAULT)
    endif
    # If current subproject is empty (the default was not defined), and we have a list of subproject
    # then make all of them
    ifeq ($$(CURRENT_SP),)
        ifneq ($$(SUBPROJECTS),)
            CURRENT_SP := allsp
         endif
    endif
    # The special allsp is handled later
    ifneq ($$(CURRENT_SP),allsp)
        # get a list of all keymaps
        KEYMAPS := $$(notdir $$(patsubst %/.,%,$$(wildcard $(ROOT_DIR)/keyboards/$$(CURRENT_KB)/keymaps/*/.)))
        ifneq ($$(CURRENT_SP),)
            # if the subproject is defined, then also look for keymaps inside the subproject folder
            SP_KEYMAPS := $$(notdir $$(patsubst %/.,%,$$(wildcard $(ROOT_DIR)/keyboards/$$(CURRENT_KB)/$$(CURRENT_SP)/keymaps/*/.)))
            KEYMAPS := $$(sort $$(KEYMAPS) $$(SP_KEYMAPS))
        endif
        # if the rule after removing the start of it is empty (we haven't specified a kemap or target)
        # compile all the keymaps
        ifeq ($$(RULE),)
            $$(eval $$(call PARSE_ALL_KEYMAPS))
        # The same if allkm was specified
        else ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,allkm),true)
            $$(eval $$(call PARSE_ALL_KEYMAPS))
        # Try to match the specified keyamp with the list of known keymaps
        else ifeq ($$(call TRY_TO_MATCH_RULE_FROM_LIST,$$(KEYMAPS)),true)
            $$(eval $$(call PARSE_KEYMAP,$$(MATCHED_ITEM)))
        # Otherwise try to match the keymap from the current folder, or arguments to the make command
        else ifneq ($$(KEYMAP),)
            $$(eval $$(call PARSE_KEYMAP,$$(KEYMAP)))
        # No matching keymap found, so we assume that the rest of the rule is the target
        # If we haven't been able to parse out a subproject, then make all of them
        # This is consistent with running make without any arguments from the keyboard
        # folder
        else ifeq ($1,)
            $$(eval $$(call PARSE_ALL_SUBPROJECTS))
        # Otherwise, make all keymaps, again this is consistent with how it works without
        # any arguments
        else
            $$(eval $$(call PARSE_ALL_KEYMAPS))
        endif
    else
        # As earlier mentioned when allsb is specified, we call our self recursively
        # for all of the subprojects
        $$(eval $$(call PARSE_ALL_IN_LIST,PARSE_SUBPROJECT,$(SUBPROJECTS)))
    endif
endef

# If we want to parse all subprojects, but the keyboard doesn't have any,
# then use defaultsp instead
define PARSE_ALL_SUBPROJECTS
    ifeq ($$(SUBPROJECTS),)
        $$(eval $$(call PARSE_SUBPROJECT,defaultsp))
    else
        $$(eval $$(call PARSE_ALL_IN_LIST,PARSE_SUBPROJECT,$$(SUBPROJECTS)))
    endif
endef

# $1 Keymap
# This is the meat of compiling a keyboard, when entering this, everything is known
# keyboard, subproject, and keymap
# Note that we are not directly calling the command here, but instead building a list,
# which will later be processed
define PARSE_KEYMAP
    CURRENT_KM = $1
    # The rest of the rule is the target
    # Remove the leading "-" from the target, as it acts as a separator
    MAKE_TARGET := $$(patsubst -%,%,$$(RULE))
    # We need to generate an unique indentifer to append to the COMMANDS list
    COMMAND := COMMAND_KEYBOARD_$$(CURRENT_KB)_SUBPROJECT_$(CURRENT_SP)_KEYMAP_$$(CURRENT_KM)
    # If we are compiling a keyboard without a subproject, we want to display just the name
    # of the keyboard, otherwise keyboard/subproject
    ifeq ($$(CURRENT_SP),)
        KB_SP := $(CURRENT_KB)
    else
        KB_SP := $(CURRENT_KB)/$$(CURRENT_SP)
    endif
    # Format it in bold
    KB_SP := $(BOLD)$$(KB_SP)$(NO_COLOR)
    # Specify the variables that we are passing forward to submake
    MAKE_VARS := KEYBOARD=$$(CURRENT_KB) SUBPROJECT=$$(CURRENT_SP) KEYMAP=$$(CURRENT_KM)
    # And the first part of the make command
    MAKE_CMD := $$(MAKE) -r -R -C $(ROOT_DIR) -f build_keyboard.mk $$(MAKE_TARGET)
    # The message to display
    MAKE_MSG := $$(MSG_MAKE_KB)
    # We run the command differently, depending on if we want more output or not
    # The true version for silent output and the false version otherwise
    $$(eval $$(call BUILD))
endef

define BUILD
    MAKE_VARS += VERBOSE=$(VERBOSE) COLOR=$(COLOR)
    COMMANDS += $$(COMMAND)
    COMMAND_true_$$(COMMAND) := \
        printf "$$(MAKE_MSG)" | \
        $$(MAKE_MSG_FORMAT); \
        LOG=$$$$($$(MAKE_CMD) $$(MAKE_VARS) SILENT=true 2>&1) ; \
        if [ $$$$? -gt 0 ]; \
            then $$(PRINT_ERROR_PLAIN); \
        elif [ "$$$$LOG" != "" ] ; \
            then $$(PRINT_WARNING_PLAIN); \
        else \
            $$(PRINT_OK); \
        fi;
    COMMAND_false_$$(COMMAND) := \
        printf "$$(MAKE_MSG)\n\n"; \
        $$(MAKE_CMD) $$(MAKE_VARS) SILENT=false; \
        if [ $$$$? -gt 0 ]; \
            then error_occurred=1; \
        fi;
endef

# Just parse all the keymaps for a specific keyboard
define PARSE_ALL_KEYMAPS
    $$(eval $$(call PARSE_ALL_IN_LIST,PARSE_KEYMAP,$$(KEYMAPS)))
endef

define BUILD_TEST
    TEST_NAME := $1
    MAKE_TARGET := $2
    COMMAND := $1
    MAKE_CMD := $$(MAKE) -r -R -C $(ROOT_DIR) -f build_test.mk $$(MAKE_TARGET)
    MAKE_VARS := TEST=$$(TEST_NAME) FULL_TESTS="$$(FULL_TESTS)"
    MAKE_MSG := $$(MSG_MAKE_TEST)
    $$(eval $$(call BUILD))
    ifneq ($$(MAKE_TARGET),clean)
        TEST_EXECUTABLE := $$(TEST_DIR)/$$(TEST_NAME).elf
        TESTS += $$(TEST_NAME)
        TEST_MSG := $$(MSG_TEST)
        $$(TEST_NAME)_COMMAND := \
            printf "$$(TEST_MSG)\n"; \
            $$(TEST_EXECUTABLE); \
            if [ $$$$? -gt 0 ]; \
                then error_occurred=1; \
            fi; \
            printf "\n";
    endif
endef

define PARSE_TEST
    TESTS :=
    TEST_NAME := $$(firstword $$(subst -, ,$$(RULE)))
    TEST_TARGET := $$(subst $$(TEST_NAME),,$$(subst $$(TEST_NAME)-,,$$(RULE)))
    ifeq ($$(TEST_NAME),all)
        MATCHED_TESTS := $$(TEST_LIST)
    else
        MATCHED_TESTS := $$(foreach TEST,$$(TEST_LIST),$$(if $$(findstring $$(TEST_NAME),$$(TEST)),$$(TEST),))
    endif
    $$(foreach TEST,$$(MATCHED_TESTS),$$(eval $$(call BUILD_TEST,$$(TEST),$$(TEST_TARGET))))
endef


# Set the silent mode depending on if we are trying to compile multiple keyboards or not
# By default it's on in that case, but it can be overridden by specifying silent=false
# from the command line
define SET_SILENT_MODE
    ifdef SUB_IS_SILENT
        SILENT_MODE := $(SUB_IS_SILENT)
    else ifeq ($$(words $$(COMMANDS)),1)
        SILENT_MODE := false
    else
        SILENT_MODE := true
    endif
endef

include $(ROOT_DIR)/message.mk

ifeq ($(strip $(BREAK_ON_ERRORS)), yes)
HANDLE_ERROR = exit 1
else
HANDLE_ERROR = echo $$error_occurred > $(ERROR_FILE)
endif

# The empty line is important here, as it will force a new shell to be created for each command
# Otherwise the command line will become too long with a lot of keyboards and keymaps
define RUN_COMMAND
+error_occurred=0;\
$(COMMAND_$(SILENT_MODE)_$(COMMAND))\
if [ $$error_occurred -gt 0 ]; then $(HANDLE_ERROR); fi;


endef
define RUN_TEST
+error_occurred=0;\
$($(TEST)_COMMAND)\
if [ $$error_occurred -gt 0 ]; then $(HANDLE_ERROR); fi;


endef

# Allow specifying just the subproject, in the keyboard directory, which will compile all keymaps
SUBPROJECTS := $(notdir $(patsubst %/Makefile,%,$(wildcard ./*/Makefile)))
.PHONY: $(SUBPROJECTS)
$(SUBPROJECTS): %: %-allkm

# Let's match everything, we handle all the rule parsing ourselves
.PHONY: %
%:
	# Check if we have the CMP tool installed
	cmp $(ROOT_DIR)/Makefile $(ROOT_DIR)/Makefile >/dev/null 2>&1; if [ $$? -gt 0 ]; then printf "$(MSG_NO_CMP)"; exit 1; fi;
	# Check if the submodules are dirty, and display a warning if they are
ifndef SKIP_GIT
	git submodule status --recursive 2>/dev/null | \
	while IFS= read -r x; do \
		case "$$x" in \
			\ *) ;; \
			*) printf "$(MSG_SUBMODULE_DIRTY)";break;; \
		esac \
	done
endif
	rm -f $(ERROR_FILE) > /dev/null 2>&1
	$(eval $(call PARSE_RULE,$@))
	$(eval $(call SET_SILENT_MODE))
	# Run all the commands in the same shell, notice the + at the first line
	# it has to be there to allow parallel execution of the submake
	# This always tries to compile everything, even if error occurs in the middle
	# But we return the error code at the end, to trigger travis failures
	$(foreach COMMAND,$(COMMANDS),$(RUN_COMMAND))
	if [ -f $(ERROR_FILE) ]; then printf "$(MSG_ERRORS)" & exit 1; fi;
	$(foreach TEST,$(TESTS),$(RUN_TEST))
	if [ -f $(ERROR_FILE) ]; then printf "$(MSG_ERRORS)" & exit 1; fi;

# All should compile everything
.PHONY: all
all: all-keyboards test-all

# Define some shortcuts, mostly for compatibility with the old syntax
.PHONY: all-keyboards
all-keyboards: allkb-allsp-allkm

.PHONY: all-keyboards-defaults
all-keyboards-defaults: allkb-allsp-default

.PHONY: test
test: test-all

.PHONY: test-clean
test-clean: test-all-clean

ifdef SKIP_VERSION
SKIP_GIT := yes
endif

# Generate the version.h file
ifndef SKIP_GIT
    GIT_VERSION := $(shell git describe --abbrev=6 --dirty --always --tags 2>/dev/null || date +"%Y-%m-%d-%H:%M:%S")
else
    GIT_VERSION := NA
endif
ifndef SKIP_VERSION
BUILD_DATE := $(shell date +"%Y-%m-%d-%H:%M:%S")
$(shell echo '#define QMK_VERSION "$(GIT_VERSION)"' > $(ROOT_DIR)/quantum/version.h)
$(shell echo '#define QMK_BUILDDATE "$(BUILD_DATE)"' >> $(ROOT_DIR)/quantum/version.h)
else
BUILD_DATE := NA
endif

include $(ROOT_DIR)/testlist.mk
