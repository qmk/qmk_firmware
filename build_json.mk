ifneq ($(EXTERNAL_USERSPACE), )
    # Look for out-of-tree json keymap file
    ifneq ("$(wildcard $(EXTERNAL_USERSPACE)/keyboards/$(KEYBOARD_FOLDER_PATH_5)/$(KEYMAP)/keymap.json)", "")
        KEYMAP_C := $(KEYBOARD_OUTPUT)/src/keymap.c
        KEYMAP_JSON := $(EXTERNAL_USERSPACE)/keyboards/$(KEYBOARD_FOLDER_PATH_5)/$(KEYMAP)/keymap.json
        KEYMAP_PATH := $(EXTERNAL_USERSPACE)/keyboards/$(KEYBOARD_FOLDER_PATH_5)/$(KEYMAP)
    else ifneq ("$(wildcard $(EXTERNAL_USERSPACE)/keyboards/$(KEYBOARD_FOLDER_PATH_4)/$(KEYMAP)/keymap.json)", "")
        KEYMAP_C := $(KEYBOARD_OUTPUT)/src/keymap.c
        KEYMAP_JSON := $(EXTERNAL_USERSPACE)/keyboards/$(KEYBOARD_FOLDER_PATH_4)/$(KEYMAP)/keymap.json
        KEYMAP_PATH := $(EXTERNAL_USERSPACE)/keyboards/$(KEYBOARD_FOLDER_PATH_4)/$(KEYMAP)
    else ifneq ("$(wildcard $(EXTERNAL_USERSPACE)/keyboards/$(KEYBOARD_FOLDER_PATH_3)/$(KEYMAP)/keymap.json)", "")
        KEYMAP_C := $(KEYBOARD_OUTPUT)/src/keymap.c
        KEYMAP_JSON := $(EXTERNAL_USERSPACE)/keyboards/$(KEYBOARD_FOLDER_PATH_3)/$(KEYMAP)/keymap.json
        KEYMAP_PATH := $(EXTERNAL_USERSPACE)/keyboards/$(KEYBOARD_FOLDER_PATH_3)/$(KEYMAP)
    else ifneq ("$(wildcard $(EXTERNAL_USERSPACE)/keyboards/$(KEYBOARD_FOLDER_PATH_2)/$(KEYMAP)/keymap.json)", "")
        KEYMAP_C := $(KEYBOARD_OUTPUT)/src/keymap.c
        KEYMAP_JSON := $(EXTERNAL_USERSPACE)/keyboards/$(KEYBOARD_FOLDER_PATH_2)/$(KEYMAP)/keymap.json
        KEYMAP_PATH := $(EXTERNAL_USERSPACE)/keyboards/$(KEYBOARD_FOLDER_PATH_2)/$(KEYMAP)
    else ifneq ("$(wildcard $(EXTERNAL_USERSPACE)/keyboards/$(KEYBOARD_FOLDER_PATH_1)/$(KEYMAP)/keymap.json)", "")
        KEYMAP_C := $(KEYBOARD_OUTPUT)/src/keymap.c
        KEYMAP_JSON := $(EXTERNAL_USERSPACE)/keyboards/$(KEYBOARD_FOLDER_PATH_1)/$(KEYMAP)/keymap.json
        KEYMAP_PATH := $(EXTERNAL_USERSPACE)/keyboards/$(KEYBOARD_FOLDER_PATH_1)/$(KEYMAP)
    endif
endif

ifeq ("$(wildcard $(KEYMAP_PATH))", "")
    # Look for in-tree json keymap file
    ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_5)/keymap.json)","")
        KEYMAP_C := $(KEYBOARD_OUTPUT)/src/keymap.c
        KEYMAP_JSON := $(MAIN_KEYMAP_PATH_5)/keymap.json
        KEYMAP_PATH := $(MAIN_KEYMAP_PATH_5)
    else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_4)/keymap.json)","")
        KEYMAP_C := $(KEYBOARD_OUTPUT)/src/keymap.c
        KEYMAP_JSON := $(MAIN_KEYMAP_PATH_4)/keymap.json
        KEYMAP_PATH := $(MAIN_KEYMAP_PATH_4)
    else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_3)/keymap.json)","")
        KEYMAP_C := $(KEYBOARD_OUTPUT)/src/keymap.c
        KEYMAP_JSON := $(MAIN_KEYMAP_PATH_3)/keymap.json
        KEYMAP_PATH := $(MAIN_KEYMAP_PATH_3)
    else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_2)/keymap.json)","")
        KEYMAP_C := $(KEYBOARD_OUTPUT)/src/keymap.c
        KEYMAP_JSON := $(MAIN_KEYMAP_PATH_2)/keymap.json
        KEYMAP_PATH := $(MAIN_KEYMAP_PATH_2)
    else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_1)/keymap.json)","")
        KEYMAP_C := $(KEYBOARD_OUTPUT)/src/keymap.c
        KEYMAP_JSON := $(MAIN_KEYMAP_PATH_1)/keymap.json
        KEYMAP_PATH := $(MAIN_KEYMAP_PATH_1)
    endif
endif

# Load the keymap-level rules.mk if exists
ifneq ("$(wildcard $(KEYMAP_PATH))", "")
    -include $(KEYMAP_PATH)/rules.mk
endif

# Generate the keymap.c
$(KEYBOARD_OUTPUT)/src/keymap.c: $(KEYMAP_JSON)
	bin/qmk json2c --quiet --output $(KEYMAP_C) $(KEYMAP_JSON)
