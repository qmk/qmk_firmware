STARTING_MAKEFILE := $(firstword $(MAKEFILE_LIST))
ROOT_MAKEFILE := $(lastword $(MAKEFILE_LIST))
ROOT_DIR := $(dir, $(ROOT_MAKEFILE))
ifeq ($(ROOT_DIR),)
    ROOT_DIR := .
endif
ABS_STARTING_MAKEFILE := $(abspath $(STARTING_MAKEFILE))
ABS_ROOT_MAKEFILE := $(abspath $(ROOT_MAKEFILE))
ABS_STARTING_DIR := $(dir $(ABS_STARTING_MAKEFILE))
ABS_ROOT_DIR := $(dir $(ABS_ROOT_MAKEFILE))
STARTING_DIR := $(subst $(ABS_ROOT_DIR),,$(ABS_STARTING_DIR))

PATH_ELEMENTS := $(subst /, ,$(STARTING_DIR))

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

$(info $(ROOT_DIR)/keyboards)
KEYBOARDS := $(notdir $(patsubst %/.,%,$(wildcard $(ROOT_DIR)/keyboards/*/.)))

$(info Keyboard: $(KEYBOARD))
$(info Keymap: $(KEYMAP))
$(info Subproject: $(SUBPROJECT))
$(info Keyboards: $(KEYBOARDS))


# Compare the start of the RULE_VARIABLE with the first argument($1)
# If the rules equals $1 or starts with $1-, RULE_FOUND is set to true
#     and $1 is removed from the RULE variable
# Otherwise the RULE_FOUND variable is set to false
# The function is a bit tricky, since there's no built in $(startswith) function
define COMPARE_AND_REMOVE_FROM_RULE
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

define PARSE_ALL_KEYBOARDS
    COMMANDS += allkb
    #$$(info $$(RULE))
    COMMAND_allkb := "All keyboards with $$(RULE)"
endef

define PARSE_KEYBOARD
    COMMANDS += $1
    #$$(info $$(RULE))
    COMMAND_$1 := "Keyboard $1 with $$(RULE)"
endef


# Recursively try to find a matching keyboard
# During the first call $1 contains a list of all keyboards
# One keyboard is checked and removed at a time
define TRY_PARSE_KEYBOARD
    CURRENT_KB := $$(firstword $1)
    $$(eval $$(call COMPARE_AND_REMOVE_FROM_RULE,$$(CURRENT_KB)))
    ifeq ($$(RULE_FOUND),true)
        $$(eval $$(call PARSE_KEYBOARD,$$(CURRENT_KB)))
    else ifneq ($1,)
        $$(eval $$(call TRY_PARSE_KEYBOARD,$$(wordlist 2,9999,$1)))
    endif
endef

define PARSE_RULE
    RULE := $1
    COMMANDS :=
    $$(eval $$(call COMPARE_AND_REMOVE_FROM_RULE,allkb))
    ifeq ($$(RULE_FOUND),true)
        $$(eval $$(call PARSE_ALL_KEYBOARDS))
    else
        $$(eval $$(call TRY_PARSE_KEYBOARD,$(KEYBOARDS)))
    endif
endef

RUN_COMMAND = echo "Running": $(COMMAND_$(COMMAND));

.PHONY: %
%:
	$(eval $(call PARSE_RULE,$@))
	$(foreach COMMAND,$(COMMANDS),$(RUN_COMMAND))

.PHONY: all-keyboards
all-keyboards: allkb

.PHONY: all-keyboards-defaults
all-keyboards-defaults: allkb-default-default

.PHONY: all
all: 
	echo "Compiling"