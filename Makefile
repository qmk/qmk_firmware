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

ifeq ($(shell git rev-parse --is-inside-work-tree 2>/dev/null),)
    export SKIP_GIT := yes
    export NOT_REPO := yes
endif

ifdef SKIP_VERSION
    export SKIP_GIT := yes
endif

ifndef SUB_IS_SILENT
ifndef SKIP_GIT
    QMK_VERSION := $(shell git describe --abbrev=0 --tags 2>/dev/null)
endif

ifneq ($(QMK_VERSION),)
$(info QMK Firmware $(QMK_VERSION))
endif
endif

# Try to determine userspace from qmk config, if set.
ifeq ($(QMK_USERSPACE),)
    QMK_USERSPACE = $(shell qmk config -ro user.overlay_dir | cut -d= -f2 | sed -e 's@^None$$@@g')
endif

# Determine which qmk cli to use
QMK_BIN := qmk

# avoid 'Entering|Leaving directory' messages
MAKEFLAGS += --no-print-directory

ON_ERROR := error_occurred=1

BREAK_ON_ERRORS = no

ROOT_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
ifeq ($(ROOT_DIR),)
    ROOT_DIR := .
endif

include paths.mk
include $(BUILDDEFS_PATH)/support.mk

TEST_OUTPUT_DIR := $(BUILD_DIR)/test
ERROR_FILE := $(BUILD_DIR)/error_occurred

.DEFAULT_GOAL := all:all


# Compare the start of the RULE variable with the first argument($1)
# If the rules equals $1 or starts with $1:, RULE_FOUND is set to true
#     and $1 is removed from the RULE variable
# Otherwise the RULE_FOUND variable is set to false, and RULE left as it was
# The function is a bit tricky, since there's no built in $(startswith) function
define COMPARE_AND_REMOVE_FROM_RULE_HELPER
    ifeq ($1,$$(RULE))
        RULE:=
        RULE_FOUND := true
    else
        STARTCOLON_REMOVED=$$(subst START$1:,,START$$(RULE))
        ifneq ($$(STARTCOLON_REMOVED),START$$(RULE))
            RULE_FOUND := true
            RULE := $$(STARTCOLON_REMOVED)
        else
            RULE_FOUND := false
        endif
    endif
endef

# This makes it easier to call COMPARE_AND_REMOVE_FROM_RULE, since it makes it behave like
# a function that returns the value
COMPARE_AND_REMOVE_FROM_RULE = $(eval $(call COMPARE_AND_REMOVE_FROM_RULE_HELPER,$1))$(RULE_FOUND)

# Try to find a match for the start of the rule to be checked
# $1 The list to be checked
# If a match is found, then RULE_FOUND is set to true
# and MATCHED_ITEM to the item that was matched
define TRY_TO_MATCH_RULE_FROM_LIST_HELPER
    # Split on ":", padding with empty strings to avoid indexing issues
    TOKEN1:=$$(shell python3 -c "import sys; print((sys.argv[1].split(':',1)+[''])[0])" $$(RULE))
    TOKENr:=$$(shell python3 -c "import sys; print((sys.argv[1].split(':',1)+[''])[1])" $$(RULE))

    FOUNDx:=$$(shell echo $1 | tr " " "\n" | grep -Fx $$(TOKEN1))
    ifneq ($$(FOUNDx),)
        RULE := $$(TOKENr)
        RULE_FOUND := true
        MATCHED_ITEM := $$(TOKEN1)
    else
        RULE_FOUND := false
        MATCHED_ITEM :=
    endif
endef

# Make it easier to call TRY_TO_MATCH_RULE_FROM_LIST
TRY_TO_MATCH_RULE_FROM_LIST = $(eval $(call TRY_TO_MATCH_RULE_FROM_LIST_HELPER,$1))$(RULE_FOUND)

# As TRY_TO_MATCH_RULE_FROM_LIST_HELPER, but with additional
# resolution of keyboard_aliases.hjson for provided rule 
define TRY_TO_MATCH_RULE_FROM_LIST_HELPER_KB
    # Split on ":", padding with empty strings to avoid indexing issues
    TOKEN1:=$$(shell python3 -c "import sys; print((sys.argv[1].split(':',1)+[''])[0])" $$(RULE))
    TOKENr:=$$(shell python3 -c "import sys; print((sys.argv[1].split(':',1)+[''])[1])" $$(RULE))

    TOKEN1:=$$(shell $(QMK_BIN) resolve-alias --allow-unknown $$(TOKEN1))

    FOUNDx:=$$(shell echo $1 | tr " " "\n" | grep -Fx $$(TOKEN1))
    ifneq ($$(FOUNDx),)
        RULE := $$(TOKENr)
        RULE_FOUND := true
        MATCHED_ITEM := $$(TOKEN1)
    else
        RULE_FOUND := false
        MATCHED_ITEM :=
    endif
endef

# Make it easier to call TRY_TO_MATCH_RULE_FROM_LIST_KB
TRY_TO_MATCH_RULE_FROM_LIST_KB = $(eval $(call TRY_TO_MATCH_RULE_FROM_LIST_HELPER_KB,$1))$(RULE_FOUND)

define ALL_IN_LIST_LOOP
    OLD_RULE$1 := $$(RULE)
    $$(eval $$(call $1,$$(ITEM$1)))
    RULE := $$(OLD_RULE$1)
endef

define PARSE_ALL_IN_LIST
    $$(foreach ITEM$1,$2,$$(eval $$(call ALL_IN_LIST_LOOP,$1)))
endef

# The entry point for rule parsing
# parses a rule in the format <keyboard>:<keymap>:<target>
# but this particular function only deals with the first <keyboard> part
define PARSE_RULE
    RULE := $1
    COMMANDS :=
    # If the rule starts with all, then continue the parsing from
    # PARSE_ALL_KEYBOARDS
    ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,all),true)
        KEYBOARD_RULE=all
        $$(eval $$(call PARSE_ALL_KEYBOARDS))
    else ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,test),true)
        $$(eval $$(call PARSE_TEST))
    # If the rule starts with the name of a known keyboard, then continue
    # the parsing from PARSE_KEYBOARD
    else ifeq ($$(call TRY_TO_MATCH_RULE_FROM_LIST_KB,$$(shell $(QMK_BIN) list-keyboards)),true)
        KEYBOARD_RULE=$$(MATCHED_ITEM)
        $$(eval $$(call PARSE_KEYBOARD,$$(MATCHED_ITEM)))
    else
        $$(info make: *** No rule to make target '$1'. Stop.)
        $$(info |)
        $$(info | QMK's make format is:)
        $$(info |     make keyboard_folder:keymap_folder[:target])
        $$(info |)
        $$(info | Where `keyboard_folder` is the path to the keyboard relative to)
        $$(info | `qmk_firmware/keyboards/`, and `keymap_folder` is the name of the)
        $$(info | keymap folder under that board's `keymaps/` directory.)
        $$(info |)
        $$(info | Examples:)
        $$(info |     keyboards/dz60, keyboards/dz60/keymaps/default)
        $$(info |       -> make dz60:default)
        $$(info |       -> qmk compile -kb dz60 -km default)
        $$(info |     keyboards/planck/rev6, keyboards/planck/keymaps/default)
        $$(info |       -> make planck/rev6:default:flash)
        $$(info |       -> qmk flash -kb planck/rev6 -km default)
        $$(info |)
    endif
endef

# $1 = Keyboard
# Parses a rule in the format <keymap>:<target>
# the keyboard is already known when entering this function
define PARSE_KEYBOARD
    # If we want to compile the default subproject, then we need to
    # include the correct makefile to determine the actual name of it
    CURRENT_KB := $1

    # 5/4/3/2/1
    KEYBOARD_FOLDER_PATH_1 := $$(CURRENT_KB)
    KEYBOARD_FOLDER_PATH_2 := $$(patsubst %/,%,$$(dir $$(KEYBOARD_FOLDER_PATH_1)))
    KEYBOARD_FOLDER_PATH_3 := $$(patsubst %/,%,$$(dir $$(KEYBOARD_FOLDER_PATH_2)))
    KEYBOARD_FOLDER_PATH_4 := $$(patsubst %/,%,$$(dir $$(KEYBOARD_FOLDER_PATH_3)))
    KEYBOARD_FOLDER_PATH_5 := $$(patsubst %/,%,$$(dir $$(KEYBOARD_FOLDER_PATH_4)))

    KEYMAPS :=
    # get a list of all keymaps
    KEYMAPS += $$(notdir $$(patsubst %/.,%,$$(wildcard $(ROOT_DIR)/keyboards/$$(KEYBOARD_FOLDER_PATH_1)/keymaps/*/.)))
    KEYMAPS += $$(notdir $$(patsubst %/.,%,$$(wildcard $(ROOT_DIR)/keyboards/$$(KEYBOARD_FOLDER_PATH_2)/keymaps/*/.)))
    KEYMAPS += $$(notdir $$(patsubst %/.,%,$$(wildcard $(ROOT_DIR)/keyboards/$$(KEYBOARD_FOLDER_PATH_3)/keymaps/*/.)))
    KEYMAPS += $$(notdir $$(patsubst %/.,%,$$(wildcard $(ROOT_DIR)/keyboards/$$(KEYBOARD_FOLDER_PATH_4)/keymaps/*/.)))
    KEYMAPS += $$(notdir $$(patsubst %/.,%,$$(wildcard $(ROOT_DIR)/keyboards/$$(KEYBOARD_FOLDER_PATH_5)/keymaps/*/.)))

    ifneq ($(QMK_USERSPACE),)
        KEYMAPS += $$(notdir $$(patsubst %/.,%,$$(wildcard $(QMK_USERSPACE)/keyboards/$$(KEYBOARD_FOLDER_PATH_1)/keymaps/*/.)))
        KEYMAPS += $$(notdir $$(patsubst %/.,%,$$(wildcard $(QMK_USERSPACE)/keyboards/$$(KEYBOARD_FOLDER_PATH_2)/keymaps/*/.)))
        KEYMAPS += $$(notdir $$(patsubst %/.,%,$$(wildcard $(QMK_USERSPACE)/keyboards/$$(KEYBOARD_FOLDER_PATH_3)/keymaps/*/.)))
        KEYMAPS += $$(notdir $$(patsubst %/.,%,$$(wildcard $(QMK_USERSPACE)/keyboards/$$(KEYBOARD_FOLDER_PATH_4)/keymaps/*/.)))
        KEYMAPS += $$(notdir $$(patsubst %/.,%,$$(wildcard $(QMK_USERSPACE)/keyboards/$$(KEYBOARD_FOLDER_PATH_5)/keymaps/*/.)))
    endif

    KEYBOARD_LAYOUTS := $(shell $(QMK_BIN) list-layouts --keyboard $1)
    LAYOUT_KEYMAPS :=
    $$(foreach LAYOUT,$$(KEYBOARD_LAYOUTS),$$(eval LAYOUT_KEYMAPS += $$(notdir $$(patsubst %/.,%,$$(wildcard $(ROOT_DIR)/layouts/*/$$(LAYOUT)/*/.)))))
    ifneq ($(QMK_USERSPACE),)
        $$(foreach LAYOUT,$$(KEYBOARD_LAYOUTS),$$(eval LAYOUT_KEYMAPS += $$(notdir $$(patsubst %/.,%,$$(wildcard $(QMK_USERSPACE)/layouts/$$(LAYOUT)/*/.)))))
    endif

    KEYMAPS := $$(sort $$(KEYMAPS) $$(LAYOUT_KEYMAPS))

    # if the rule after removing the start of it is empty (we haven't specified a kemap or target)
    # compile all the keymaps
    ifeq ($$(RULE),)
        $$(eval $$(call PARSE_ALL_KEYMAPS))
    # The same if all was specified
    else ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,all),true)
        $$(eval $$(call PARSE_ALL_KEYMAPS))
    # List all keymaps for the given keyboard
    else ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,list-keymaps),true)
        $$(eval $$(call LIST_ALL_KEYMAPS))
    # Try to match the specified keyamp with the list of known keymaps
    else ifeq ($$(call TRY_TO_MATCH_RULE_FROM_LIST,$$(KEYMAPS)),true)
        $$(eval $$(call PARSE_KEYMAP,$$(MATCHED_ITEM)))
    # Otherwise try to match the keymap from the current folder, or arguments to the make command
    else ifneq ($$(KEYMAP),)
        $$(eval $$(call PARSE_KEYMAP,$$(KEYMAP)))
    # Otherwise if we are running make all:<user> just skip
    else ifeq ($$(KEYBOARD_RULE),all)
        # $$(info Skipping: No user keymap for $$(CURRENT_KB))
    # Otherwise, make all keymaps, again this is consistent with how it works without
    # any arguments
    else
        $$(eval $$(call PARSE_ALL_KEYMAPS))
    endif
endef

# if we are going to compile all keyboards, match the rest of the rule
# for each of them
define PARSE_ALL_KEYBOARDS
    $$(eval $$(call PARSE_ALL_IN_LIST,PARSE_KEYBOARD,$(shell $(QMK_BIN) list-keyboards)))
endef

# Prints a list of all known keymaps for the given keyboard
define LIST_ALL_KEYMAPS
    COMMAND_true_LIST_KEYMAPS := \
        printf "$$(KEYMAPS)\n";
    COMMAND_false_LIST_KEYMAPS := \
        printf "$$(MSG_AVAILABLE_KEYMAPS)\n"; \
        printf "$$(KEYMAPS)\n";
    COMMANDS += LIST_KEYMAPS
endef

# $1 Keymap
# This is the meat of compiling a keyboard, when entering this, everything is known
# keyboard, subproject, and keymap
# Note that we are not directly calling the command here, but instead building a list,
# which will later be processed
define PARSE_KEYMAP
    CURRENT_KM = $1
    # The rest of the rule is the target
    # Remove the leading ":" from the target, as it acts as a separator
    MAKE_TARGET := $$(patsubst :%,%,$$(RULE))
    # We need to generate an unique identifier to append to the COMMANDS list
    CURRENT_KB_UNDER := $$(subst /,_,$$(CURRENT_KB))
    COMMAND := COMMAND_KEYBOARD_$$(CURRENT_KB_UNDER)_KEYMAP_$$(CURRENT_KM)
    # If we are compiling a keyboard without a subproject, we want to display just the name
    # of the keyboard, otherwise keyboard/subproject
    KB_SP := $$(CURRENT_KB)
    # Format it in bold
    KB_SP := $(BOLD)$$(KB_SP)$(NO_COLOR)
    # Specify the variables that we are passing forward to submake
    MAKE_VARS := KEYBOARD=$$(CURRENT_KB) KEYMAP=$$(CURRENT_KM) QMK_BIN=$$(QMK_BIN)
    # And the first part of the make command
    MAKE_CMD := $$(MAKE) -r -R -C $(ROOT_DIR) -f $(BUILDDEFS_PATH)/build_keyboard.mk $$(MAKE_TARGET)
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
        elif [ "$$$$LOG" = "skipped" ] ; \
            then $$(PRINT_SKIPPED_PLAIN); \
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
    TEST_PATH := $1
    TEST_NAME := $$(notdir $$(TEST_PATH))
    TEST_FULL_NAME := $$(subst /,_,$$(patsubst $$(ROOT_DIR)tests/%,%,$$(TEST_PATH)))
    MAKE_TARGET := $2
    COMMAND := $1
    MAKE_CMD := $$(MAKE) -r -R -C $(ROOT_DIR) -f $(BUILDDEFS_PATH)/build_test.mk $$(MAKE_TARGET)
    MAKE_VARS := TEST=$$(TEST_NAME) TEST_OUTPUT=$$(TEST_FULL_NAME) TEST_PATH=$$(TEST_PATH) FULL_TESTS="$$(FULL_TESTS)"
    MAKE_MSG := $$(MSG_MAKE_TEST)
    $$(eval $$(call BUILD))
    ifneq ($$(MAKE_TARGET),clean)
        TEST_EXECUTABLE := $$(TEST_OUTPUT_DIR)/$$(TEST_FULL_NAME).elf
        TESTS += $$(TEST_FULL_NAME)
        TEST_MSG := $$(MSG_TEST)
        $$(TEST_FULL_NAME)_COMMAND := \
            printf "$$(TEST_MSG)\n"; \
            $$(TEST_EXECUTABLE); \
            if [ $$$$? -gt 0 ]; \
                then error_occurred=1; \
            fi; \
            printf "\n";
    endif
endef

define LIST_TEST
    include $(BUILDDEFS_PATH)/testlist.mk
    FOUND_TESTS := $$(patsubst ./tests/%,%,$$(TEST_LIST))
    $$(info $$(FOUND_TESTS))
endef

define PARSE_TEST
    TESTS :=
    TEST_NAME := $$(firstword $$(subst :, ,$$(RULE)))
    TEST_TARGET := $$(subst $$(TEST_NAME),,$$(subst $$(TEST_NAME):,,$$(RULE)))
    include $(BUILDDEFS_PATH)/testlist.mk
    ifeq ($$(TEST_NAME),all)
        MATCHED_TESTS := $$(TEST_LIST)
    else
        MATCHED_TESTS := $$(foreach TEST, $$(TEST_LIST),$$(if $$(findstring x$$(TEST_NAME)x, x$$(patsubst ./tests/%,%,$$(TEST)x)), $$(TEST),))
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

include $(BUILDDEFS_PATH)/message.mk

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

# Catch everything and parse the command line ourselves.
.PHONY: %
%:
	# Ensure that $(QMK_BIN) works.
	if ! $(QMK_BIN) hello 1> /dev/null 2>&1; then printf "$(MSG_PYTHON_MISSING)"; exit 1; fi
ifdef NOT_REPO
	printf "$(MSG_NOT_REPO)"
endif
ifndef SKIP_GIT
	$(QMK_BIN) git-submodule --sync
	# Check if the submodules are dirty, and display a warning if they are
	if ! $(QMK_BIN) git-submodule --check 1> /dev/null 2>&1; then printf "$(MSG_SUBMODULE_DIRTY)"; fi
endif
	rm -f $(ERROR_FILE) > /dev/null 2>&1
	$(eval $(call PARSE_RULE,$@))
	$(eval $(call SET_SILENT_MODE))
	# Run all the commands in the same shell, notice the + at the first line
	# it has to be there to allow parallel execution of the submake
	# This always tries to compile everything, even if error occurs in the middle
	# But we return the error code at the end, to trigger travis failures
	# The sort at this point is to remove duplicates
	$(foreach COMMAND,$(sort $(COMMANDS)),$(RUN_COMMAND))
	if [ -f $(ERROR_FILE) ]; then printf "$(MSG_ERRORS)" & exit 1; fi;
	$(foreach TEST,$(sort $(TESTS)),$(RUN_TEST))
	if [ -f $(ERROR_FILE) ]; then printf "$(MSG_ERRORS)" & exit 1; fi;

lib/%:
	git submodule sync $?
	git submodule update --init $?

.PHONY: git-submodule
git-submodule:
	$(QMK_BIN) git-submodule

.PHONY: git-submodules
git-submodules: git-submodule

.PHONY: list-keyboards
list-keyboards:
	$(QMK_BIN) list-keyboards | tr '\n' ' '

.PHONY: list-tests
list-tests:
	$(eval $(call LIST_TEST))

.PHONY: generate-keyboards-file
generate-keyboards-file:
	$(QMK_BIN) list-keyboards

.PHONY: clean
clean:
	echo -n 'Deleting .build/ ... '
	rm -rf $(BUILD_DIR)
	echo 'done.'

.PHONY: distclean distclean_qmk
distclean: distclean_qmk
distclean_qmk: clean
	echo -n 'Deleting *.bin, *.hex, and *.uf2 ... '
	rm -f *.bin *.hex *.uf2
	echo 'done.'

ifneq ($(QMK_USERSPACE),)
.PHONY: distclean_userspace
distclean: distclean_userspace
distclean_userspace: clean
	echo -n 'Deleting userspace *.bin, *.hex, and *.uf2 ... '
	rm -f $(QMK_USERSPACE)/*.bin $(QMK_USERSPACE)/*.hex $(QMK_USERSPACE)/*.uf2
	echo 'done.'
endif

# Extra targets for formatting and/or pytest, running within the qmk/qmk_cli container to match GHA.
CONTAINER_PREAMBLE := export HOME="/tmp"; export PATH="/tmp/.local/bin:\$$PATH"; python3 -m pip install --upgrade pip; python3 -m pip install -r requirements-dev.txt

.PHONY: format-core
format-core:
	RUNTIME=docker ./util/docker_cmd.sh bash -lic "$(CONTAINER_PREAMBLE); qmk format-c --core-only -a && qmk format-python -a"

.PHONY: pytest
pytest:
	RUNTIME=docker ./util/docker_cmd.sh bash -lic "$(CONTAINER_PREAMBLE); qmk pytest"

.PHONY: format-and-pytest
format-and-pytest:
	RUNTIME=docker ./util/docker_cmd.sh bash -lic "$(CONTAINER_PREAMBLE); qmk format-c --core-only -a && qmk format-python -a && qmk pytest"
