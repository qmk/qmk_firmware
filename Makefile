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

ifndef SUB_IS_SILENT
ifndef SKIP_GIT
    QMK_VERSION := $(shell git describe --abbrev=0 --tags 2>/dev/null)
endif

ifneq ($(QMK_VERSION),)
$(info QMK Firmware $(QMK_VERSION))
endif
endif

# Determine which qmk cli to use
ifeq (,$(shell which qmk))
    QMK_BIN = bin/qmk
else
    QMK_BIN = qmk
endif

# avoid 'Entering|Leaving directory' messages
MAKEFLAGS += --no-print-directory

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


# Phony targets to enable a few simple make commands outside the main processing below.
.PHONY: list-keyboards
list-keyboards:
	util/list_keyboards.sh | sort -u | tr '\n' ' '

.PHONY: generate-keyboards-file
generate-keyboards-file:
	util/list_keyboards.sh | sort -u

.PHONY: clean
clean:
	echo -n 'Deleting .build/ ... '
	rm -rf $(BUILD_DIR)
	echo 'done.'

.PHONY: distclean
distclean: clean
	echo -n 'Deleting *.bin, *.hex, and *.uf2 ... '
	rm -f *.bin *.hex *.uf2
	echo 'done.'

#Compatibility with the old make variables, anything you specify directly on the command line
# always overrides the detected folders
ifdef keyboard
    KEYBOARD := $(keyboard)
endif
ifdef keymap
    KEYMAP := $(keymap)
endif

# Uncomment these for debugging
# $(info Keyboard: $(KEYBOARD))
# $(info Keymap: $(KEYMAP))


# Set the default goal depending on where we are running make from
# this handles the case where you run make without any arguments
.DEFAULT_GOAL := all:all
ifneq ($(KEYMAP),)
    .DEFAULT_GOAL := $(KEYBOARD):$(KEYMAP)
else ifneq ($(KEYBOARD),)
     # Inside a keyboard folder, build all keymaps for all subprojects
     # Note that this is different from the old behaviour, which would
     # build only the default keymap of the default keyboard
    .DEFAULT_GOAL := $(KEYBOARD):all
endif


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
# parses a rule in the format <keyboard>:<keymap>:<target>
# but this particular function only deals with the first <keyboard> part
define PARSE_RULE
    RULE := $1
    COMMANDS :=
    REQUIRE_PLATFORM_KEY :=
    # If the rule starts with all, then continue the parsing from
    # PARSE_ALL_KEYBOARDS
    ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,all),true)
        KEYBOARD_RULE=all
        $$(eval $$(call PARSE_ALL_KEYBOARDS))
    else ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,all-avr),true)
        KEYBOARD_RULE=all
        REQUIRE_PLATFORM_KEY := avr
        $$(eval $$(call PARSE_ALL_KEYBOARDS))
    else ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,all-chibios),true)
        KEYBOARD_RULE=all
        REQUIRE_PLATFORM_KEY := chibios
        $$(eval $$(call PARSE_ALL_KEYBOARDS))
    else ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,all-arm_atsam),true)
        KEYBOARD_RULE=all
        REQUIRE_PLATFORM_KEY := arm_atsam
        $$(eval $$(call PARSE_ALL_KEYBOARDS))
    else ifeq ($$(call COMPARE_AND_REMOVE_FROM_RULE,test),true)
        $$(eval $$(call PARSE_TEST))
    # If the rule starts with the name of a known keyboard, then continue
    # the parsing from PARSE_KEYBOARD
    else ifeq ($$(call TRY_TO_MATCH_RULE_FROM_LIST,$$(shell util/list_keyboards.sh | sort -u)),true)
        KEYBOARD_RULE=$$(MATCHED_ITEM)
        $$(eval $$(call PARSE_KEYBOARD,$$(MATCHED_ITEM)))
    # Otherwise use the KEYBOARD variable, which is determined either by
    # the current directory you run make from, or passed in as an argument
    else ifneq ($$(KEYBOARD),)
        $$(eval $$(call PARSE_KEYBOARD,$$(KEYBOARD)))
    else
        $$(info make: *** No rule to make target '$1'. Stop.)
        $$(info |)
        $$(info |  QMK's make format recently changed to use folder locations and colons:)
        $$(info |     make project_folder:keymap[:target])
        $$(info |  Examples:)
        $$(info |     make dz60:default)
        $$(info |     make planck/rev6:default:flash)
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

    # KEYBOARD_FOLDERS := $$(subst /, , $(CURRENT_KB))

    DEFAULT_FOLDER := $$(CURRENT_KB)

    # We assume that every rules.mk will contain the full default value
    $$(eval include $(ROOT_DIR)/keyboards/$$(CURRENT_KB)/rules.mk)
    ifneq ($$(DEFAULT_FOLDER),$$(CURRENT_KB))
        $$(eval include $(ROOT_DIR)/keyboards/$$(DEFAULT_FOLDER)/rules.mk)
    endif
    CURRENT_KB := $$(DEFAULT_FOLDER)

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
    # this might be needed, but in a different form
    #KEYMAPS := $$(sort $$(filter-out $$(KEYBOARD_FOLDER_1) $$(KEYBOARD_FOLDER_2) \
        $$(KEYBOARD_FOLDER_3) $$(KEYBOARD_FOLDER_4) $$(KEYBOARD_FOLDER_5), $$(KEYMAPS)))

    KEYBOARD_LAYOUTS :=
    ifneq ("$$(wildcard $(ROOT_DIR)/keyboards/$$(KEYBOARD_FOLDER_PATH_5)/rules.mk)","")
      LAYOUTS :=
      $$(eval include $(ROOT_DIR)/keyboards/$$(KEYBOARD_FOLDER_PATH_5)/rules.mk)
      KEYBOARD_LAYOUTS := $$(sort $$(LAYOUTS) $$(KEYBOARD_LAYOUTS))
    endif
    ifneq ("$$(wildcard $(ROOT_DIR)/keyboards/$$(KEYBOARD_FOLDER_PATH_4)/rules.mk)","")
      LAYOUTS :=
      $$(eval include $(ROOT_DIR)/keyboards/$$(KEYBOARD_FOLDER_PATH_4)/rules.mk)
      KEYBOARD_LAYOUTS := $$(sort $$(LAYOUTS) $$(KEYBOARD_LAYOUTS))
    endif
    ifneq ("$$(wildcard $(ROOT_DIR)/keyboards/$$(KEYBOARD_FOLDER_PATH_3)/rules.mk)","")
      LAYOUTS :=
      $$(eval include $(ROOT_DIR)/keyboards/$$(KEYBOARD_FOLDER_PATH_3)/rules.mk)
      KEYBOARD_LAYOUTS := $$(sort $$(LAYOUTS) $$(KEYBOARD_LAYOUTS))
    endif
    ifneq ("$$(wildcard $(ROOT_DIR)/keyboards/$$(KEYBOARD_FOLDER_PATH_2)/rules.mk)","")
      LAYOUTS :=
      $$(eval include $(ROOT_DIR)/keyboards/$$(KEYBOARD_FOLDER_PATH_2)/rules.mk)
      KEYBOARD_LAYOUTS := $$(sort $$(LAYOUTS) $$(KEYBOARD_LAYOUTS))
    endif
    ifneq ("$$(wildcard $(ROOT_DIR)/keyboards/$$(KEYBOARD_FOLDER_PATH_1)/rules.mk)","")
      LAYOUTS :=
      $$(eval include $(ROOT_DIR)/keyboards/$$(KEYBOARD_FOLDER_PATH_1)/rules.mk)
      KEYBOARD_LAYOUTS := $$(sort $$(LAYOUTS) $$(KEYBOARD_LAYOUTS))
    endif

    LAYOUT_KEYMAPS :=
    $$(foreach LAYOUT,$$(KEYBOARD_LAYOUTS),$$(eval LAYOUT_KEYMAPS += $$(notdir $$(patsubst %/.,%,$$(wildcard $(ROOT_DIR)/layouts/*/$$(LAYOUT)/*/.)))))

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
    $$(eval $$(call PARSE_ALL_IN_LIST,PARSE_KEYBOARD,$(shell util/list_keyboards.sh noci | sort -u)))
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
    # We need to generate an unique indentifer to append to the COMMANDS list
    CURRENT_KB_UNDER := $$(subst /,_,$$(CURRENT_KB))
    COMMAND := COMMAND_KEYBOARD_$$(CURRENT_KB_UNDER)_KEYMAP_$$(CURRENT_KM)
    # If we are compiling a keyboard without a subproject, we want to display just the name
    # of the keyboard, otherwise keyboard/subproject
    KB_SP := $$(CURRENT_KB)
    # Format it in bold
    KB_SP := $(BOLD)$$(KB_SP)$(NO_COLOR)
    # Specify the variables that we are passing forward to submake
    MAKE_VARS := KEYBOARD=$$(CURRENT_KB) KEYMAP=$$(CURRENT_KM) REQUIRE_PLATFORM_KEY=$$(REQUIRE_PLATFORM_KEY) QMK_BIN=$$(QMK_BIN)
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
    TEST_NAME := $$(firstword $$(subst :, ,$$(RULE)))
    TEST_TARGET := $$(subst $$(TEST_NAME),,$$(subst $$(TEST_NAME):,,$$(RULE)))
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

# Catch everything and parse the command line ourselves.
.PHONY: %
%:
	# Check if we have the CMP tool installed
	cmp $(ROOT_DIR)/Makefile $(ROOT_DIR)/Makefile >/dev/null 2>&1; if [ $$? -gt 0 ]; then printf "$(MSG_NO_CMP)"; exit 1; fi;
	# Ensure that $(QMK_BIN) works.
	if ! $(QMK_BIN) hello 1> /dev/null 2>&1; then printf "$(MSG_PYTHON_MISSING)"; exit 1; fi
	# Check if the submodules are dirty, and display a warning if they are
ifndef SKIP_GIT
	if [ ! -e lib/chibios ]; then git submodule sync lib/chibios && git submodule update --depth 50 --init lib/chibios; fi
	if [ ! -e lib/chibios-contrib ]; then git submodule sync lib/chibios-contrib && git submodule update --depth 50 --init lib/chibios-contrib; fi
	if [ ! -e lib/ugfx ]; then git submodule sync lib/ugfx && git submodule update --depth 50 --init lib/ugfx; fi
	if [ ! -e lib/lufa ]; then git submodule sync lib/lufa && git submodule update --depth 50 --init lib/lufa; fi
	if [ ! -e lib/vusb ]; then git submodule sync lib/vusb && git submodule update --depth 50 --init lib/vusb; fi
	if [ ! -e lib/printf ]; then git submodule sync lib/printf && git submodule update --depth 50 --init lib/printf; fi
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
	git submodule sync --recursive
	git submodule update --init --recursive --progress

ifdef SKIP_VERSION
SKIP_GIT := yes
endif

# Generate the version.h file
ifndef SKIP_GIT
    GIT_VERSION := $(shell git describe --abbrev=6 --dirty --always --tags 2>/dev/null || date +"%Y-%m-%d-%H:%M:%S")
    CHIBIOS_VERSION := $(shell cd lib/chibios && git describe --abbrev=6 --dirty --always --tags 2>/dev/null || date +"%Y-%m-%d-%H:%M:%S")
    CHIBIOS_CONTRIB_VERSION := $(shell cd lib/chibios-contrib && git describe --abbrev=6 --dirty --always --tags 2>/dev/null || date +"%Y-%m-%d-%H:%M:%S")
else
    GIT_VERSION := NA
    CHIBIOS_VERSION := NA
    CHIBIOS_CONTRIB_VERSION := NA
endif
ifndef SKIP_VERSION
BUILD_DATE := $(shell date +"%Y-%m-%d-%H:%M:%S")
else
BUILD_DATE := 2020-01-01-00:00:00
endif

$(shell echo '#define QMK_VERSION "$(GIT_VERSION)"' > $(ROOT_DIR)/quantum/version.h)
$(shell echo '#define QMK_BUILDDATE "$(BUILD_DATE)"' >> $(ROOT_DIR)/quantum/version.h)
$(shell echo '#define CHIBIOS_VERSION "$(CHIBIOS_VERSION)"' >> $(ROOT_DIR)/quantum/version.h)
$(shell echo '#define CHIBIOS_CONTRIB_VERSION "$(CHIBIOS_CONTRIB_VERSION)"' >> $(ROOT_DIR)/quantum/version.h)

include $(ROOT_DIR)/testlist.mk
