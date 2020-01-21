LAYOUTS_PATH := layouts
LAYOUTS_REPOS := $(patsubst %/,%,$(sort $(dir $(wildcard $(LAYOUTS_PATH)/*/))))
USER_LAYOUTS_PATH := users
USER_LAYOUTS_REPOS := $(patsubst %/,%,$(sort $(dir $(wildcard $(USER_LAYOUTS_PATH)/*/$(LAYOUTS_PATH)/))))

define SEARCH_LAYOUTS_REPO
    LAYOUT_KEYMAP_PATH := $$(LAYOUTS_REPO)/$$(LAYOUT)/$$(KEYMAP)
    LAYOUT_KEYMAP_C := $$(LAYOUT_KEYMAP_PATH)/keymap.c
    ifneq ("$$(wildcard $$(LAYOUT_KEYMAP_C))","")
        -include $$(LAYOUT_KEYMAP_PATH)/rules.mk
        KEYMAP_C := $$(LAYOUT_KEYMAP_C)
        KEYMAP_PATH := $$(LAYOUT_KEYMAP_PATH)
    endif
endef

define SEARCH_USER_LAYOUTS_REPO
    USER_LAYOUT_KEYMAP_PATH := $$(USER_LAYOUTS_REPO)/$$(LAYOUT)
    USER_LAYOUT_KEYMAP_C := $$(USER_LAYOUT_KEYMAP_PATH)/keymap.c
    ifneq ("$$(wildcard $$(USER_LAYOUT_KEYMAP_C))","")
        -include $$(USER_LAYOUT_KEYMAP_PATH)/rules.mk
        KEYMAP_C := $$(USER_LAYOUT_KEYMAP_C)
        KEYMAP_PATH := $$(USER_LAYOUT_KEYMAP_PATH)
    endif
endef

define SEARCH_LAYOUTS
    $$(foreach LAYOUTS_REPO,$$(LAYOUTS_REPOS),$$(eval $$(call SEARCH_LAYOUTS_REPO)))
    ifeq ("$$(wildcard $$(KEYMAP_C))","")
        $$(foreach USER_LAYOUTS_REPO,$$(USER_LAYOUTS_REPOS),$$(eval $$(call SEARCH_USER_LAYOUTS_REPO)))
    endif
endef

ifneq ($(FORCE_LAYOUT),)
    ifneq (,$(findstring $(FORCE_LAYOUT),$(LAYOUTS)))
        $(info Forcing layout: $(FORCE_LAYOUT))
        LAYOUTS := $(FORCE_LAYOUT)
    else
        $(error Forced layout does not exist)
    endif
endif

$(foreach LAYOUT,$(LAYOUTS),$(eval $(call SEARCH_LAYOUTS)))
