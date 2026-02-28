# Look for a json keymap file
ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_5)/keymap.json)","")
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_5)/keymap.json
    KEYMAP_JSON_PATH := $(MAIN_KEYMAP_PATH_5)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_4)/keymap.json)","")
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_4)/keymap.json
    KEYMAP_JSON_PATH := $(MAIN_KEYMAP_PATH_4)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_3)/keymap.json)","")
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_3)/keymap.json
    KEYMAP_JSON_PATH := $(MAIN_KEYMAP_PATH_3)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_2)/keymap.json)","")
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_2)/keymap.json
    KEYMAP_JSON_PATH := $(MAIN_KEYMAP_PATH_2)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_1)/keymap.json)","")
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_1)/keymap.json
    KEYMAP_JSON_PATH := $(MAIN_KEYMAP_PATH_1)
endif

ifneq ($(QMK_USERSPACE),)
    ifneq ("$(wildcard $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_5)/keymap.json)","")
        KEYMAP_JSON := $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_5)/keymap.json
        KEYMAP_JSON_PATH := $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_5)
    else ifneq ("$(wildcard $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_4)/keymap.json)","")
        KEYMAP_JSON := $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_4)/keymap.json
        KEYMAP_JSON_PATH := $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_4)
    else ifneq ("$(wildcard $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_3)/keymap.json)","")
        KEYMAP_JSON := $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_3)/keymap.json
        KEYMAP_JSON_PATH := $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_3)
    else ifneq ("$(wildcard $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_2)/keymap.json)","")
        KEYMAP_JSON := $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_2)/keymap.json
        KEYMAP_JSON_PATH := $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_2)
    else ifneq ("$(wildcard $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_1)/keymap.json)","")
        KEYMAP_JSON := $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_1)/keymap.json
        KEYMAP_JSON_PATH := $(QMK_USERSPACE)/$(MAIN_KEYMAP_PATH_1)
    endif
endif
