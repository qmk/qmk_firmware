LAYOUTS_PATH := layouts
LAYOUTS_REPOS := $(patsubst %/,%,$(sort $(dir $(wildcard $(LAYOUTS_PATH)/*/))))

ifneq ($(QMK_USERSPACE),)
    LAYOUTS_REPOS += $(patsubst %/,%,$(QMK_USERSPACE)/$(LAYOUTS_PATH))
endif

define SEARCH_LAYOUTS_REPO
    LAYOUT_KEYMAP_PATH := $$(LAYOUTS_REPO)/$$(LAYOUT)/$$(KEYMAP)
    LAYOUT_KEYMAP_JSON := $$(LAYOUT_KEYMAP_PATH)/keymap.json
    LAYOUT_KEYMAP_C := $$(LAYOUT_KEYMAP_PATH)/keymap.c
    ifneq ("$$(wildcard $$(LAYOUT_KEYMAP_JSON))","")
        KEYMAP_JSON := $$(LAYOUT_KEYMAP_JSON)
        KEYMAP_JSON_PATH := $$(LAYOUT_KEYMAP_PATH)
    endif
    ifneq ("$$(wildcard $$(LAYOUT_KEYMAP_C))","")
        -include $$(LAYOUT_KEYMAP_PATH)/rules.mk
        KEYMAP_C := $$(LAYOUT_KEYMAP_C)
        KEYMAP_PATH := $$(LAYOUT_KEYMAP_PATH)
    endif
endef

define SEARCH_LAYOUTS
    $$(foreach LAYOUTS_REPO,$$(LAYOUTS_REPOS),$$(eval $$(call SEARCH_LAYOUTS_REPO)))
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
