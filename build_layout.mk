LAYOUTS_PATH := layouts

define SEARCH_LAYOUTS
	LAYOUT_KEYMAP_PATH := $$(LAYOUTS_PATH)/$1/$$(KEYMAP)
	LAYOUT_KEYMAP_C := $$(LAYOUT_KEYMAP_PATH)/keymap.c
	ifneq ("$$(wildcard $$(LAYOUT_KEYMAP_C))","")
	    -include $$(LAYOUT_KEYMAP_PATH)/rules.mk
	    KEYMAP_C := $$(LAYOUT_KEYMAP_C)
	    KEYMAP_PATH := $$(LAYOUT_KEYMAP_PATH)
	endif
endef

$(foreach LAYOUT,$(LAYOUTS),$(eval $(call SEARCH_LAYOUTS,$(LAYOUT))))