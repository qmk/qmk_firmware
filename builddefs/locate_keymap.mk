MAIN_KEYMAP_PATH_1 := $(KEYBOARD_PATH_1)/keymaps/$(KEYMAP)
MAIN_KEYMAP_PATH_2 := $(KEYBOARD_PATH_2)/keymaps/$(KEYMAP)
MAIN_KEYMAP_PATH_3 := $(KEYBOARD_PATH_3)/keymaps/$(KEYMAP)
MAIN_KEYMAP_PATH_4 := $(KEYBOARD_PATH_4)/keymaps/$(KEYMAP)
MAIN_KEYMAP_PATH_5 := $(KEYBOARD_PATH_5)/keymaps/$(KEYMAP)

POTENTIAL_KEYMAP_PATHS += $(MAIN_KEYMAP_PATH_1)
POTENTIAL_KEYMAP_PATHS += $(MAIN_KEYMAP_PATH_2)
POTENTIAL_KEYMAP_PATHS += $(MAIN_KEYMAP_PATH_3)
POTENTIAL_KEYMAP_PATHS += $(MAIN_KEYMAP_PATH_4)
POTENTIAL_KEYMAP_PATHS += $(MAIN_KEYMAP_PATH_5)

ifneq ($(QMK_USERSPACE),)
    POTENTIAL_KEYMAP_PATHS += $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_1)
    POTENTIAL_KEYMAP_PATHS += $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_2)
    POTENTIAL_KEYMAP_PATHS += $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_3)
    POTENTIAL_KEYMAP_PATHS += $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_4)
    POTENTIAL_KEYMAP_PATHS += $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_5)
endif

define SEARCH_POTENTIAL_LOCATION
    POTENTIAL_DIR := $1
    ifeq ("$$(wildcard $$(KEYMAP_PATH))", "")
        POTENTIAL_KEYMAP_JSON := $$(POTENTIAL_DIR)/keymap.json
        POTENTIAL_KEYMAP_C := $$(POTENTIAL_DIR)/keymap.c
        ifneq ("$$(wildcard $$(POTENTIAL_KEYMAP_JSON))","")
            KEYMAP_JSON := $$(POTENTIAL_KEYMAP_JSON)
            KEYMAP_PATH := $$(POTENTIAL_DIR)
        endif
        ifneq ("$$(wildcard $$(POTENTIAL_KEYMAP_C))","")
            KEYMAP_C := $$(POTENTIAL_KEYMAP_C)
            KEYMAP_PATH := $$(POTENTIAL_DIR)
        endif
    endif
endef

$(foreach KM_DIR,$(POTENTIAL_KEYMAP_PATHS),$(eval $(call SEARCH_POTENTIAL_LOCATION, $(KM_DIR))))

LAYOUTS_PATH := layouts
LAYOUTS_REPOS := $(patsubst %/,%,$(sort $(dir $(wildcard $(LAYOUTS_PATH)/*/))))

ifneq ($(QMK_USERSPACE),)
    LAYOUTS_REPOS += $(patsubst %/,%,$(QMK_USERSPACE)/$(LAYOUTS_PATH))
endif

define SEARCH_LAYOUTS
    $$(foreach LAYOUTS_REPO,$$(LAYOUTS_REPOS),$$(eval $$(call SEARCH_POTENTIAL_LOCATION,$$(LAYOUTS_REPO)/$$(LAYOUT)/$$(KEYMAP))))
endef

ifneq ($(FORCE_LAYOUT),)
    ifneq (,$(findstring $(FORCE_LAYOUT),$(LAYOUTS)))
        $(info Forcing layout: $(FORCE_LAYOUT))
        LAYOUTS := $(FORCE_LAYOUT)
    else
        $(call CATASTROPHIC_ERROR,Invalid layout,Forced layout does not exist)
    endif
endif

$(foreach LAYOUT,$(LAYOUTS),$(eval $(call SEARCH_LAYOUTS)))

ifeq ("$$(wildcard $$(KEYMAP_PATH))", "")
    $(call CATASTROPHIC_ERROR,Invalid keymap,Could not find keymap)
    # this state should never be reached
endif
