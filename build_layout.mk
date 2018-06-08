LAYOUTS_PATH := layouts
LAYOUTS_REPOS := $(patsubst %/,%,$(sort $(dir $(wildcard $(LAYOUTS_PATH)/*/))))

define SEARCH_LAYOUTS_REPO
    LAYOUT_KEYMAP_PATH := $$(LAYOUTS_REPO)/$$(LAYOUT)/$$(KEYMAP)
    PARENT_LAYOUT_KEYMAP_PATH := $(patsubst %/,%,$(dir $(LAYOUT_KEYMAP_PATH)))
    LAYOUT_KEYMAP_C := $$(LAYOUT_KEYMAP_PATH)/keymap.c
    PARENT_LAYOUT_KEYMAP_C := $$(PARENT_LAYOUT_KEYMAP_PATH)/keymap.c
    ifneq ("$$(wildcard $$(LAYOUT_KEYMAP_C))","")
        KEYMAP_C := $$(LAYOUT_KEYMAP_C)
        KEYMAP_PATH := $$(LAYOUT_KEYMAP_PATH)
    else ifneq ("$$(wildcard $$(PARENT_LAYOUT_KEYMAP_C))","")
        KEYMAP_C := $$(PARENT_LAYOUT_KEYMAP_C)
        KEYMAP_PATH := $$(LAYOUT_KEYMAP_PATH)
    endif
endef

define SEARCH_LAYOUTS
    $$(foreach LAYOUTS_REPO,$$(LAYOUTS_REPOS),$$(eval $$(call SEARCH_LAYOUTS_REPO)))
endef

$(foreach LAYOUT,$(LAYOUTS),$(eval $(call SEARCH_LAYOUTS)))
