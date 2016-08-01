STARTING_MAKEFILE := $(firstword $(MAKEFILE_LIST))
ROOT_MAKEFILE := $(lastword $(MAKEFILE_LIST))
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

$(info Keyboard: $(KEYBOARD))
$(info Keymap: $(KEYMAP))
$(info Subproject: $(SUBPROJECT))


all: 
	echo "Compiling"