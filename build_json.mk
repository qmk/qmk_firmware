# Look for a json keymap file
ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_5)/keymap.json)","")
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_5)/keymap.json
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH_5)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_4)/keymap.json)","")
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_4)/keymap.json
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH_4)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_3)/keymap.json)","")
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_3)/keymap.json
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH_3)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_2)/keymap.json)","")
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_2)/keymap.json
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH_2)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_1)/keymap.json)","")
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_1)/keymap.json
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH_1)
endif

# Have we found a keymap.json?
ifneq ("$(wildcard $(KEYMAP_JSON))", "")
    KEYMAP_C := $(KEYBOARD_OUTPUT)/src/build_json_keymap.c
    KEYMAP_H := $(KEYBOARD_OUTPUT)/src/build_json_config.h

    # Load the keymap-level rules.mk if exists
    -include $(KEYMAP_PATH)/rules.mk

    # Load any rules.mk content from keymap.json
    INFO_RULES_MK = $(shell bin/qmk generate-rules-mk --quiet --escape --keyboard $(KEYBOARD) --keymap $(KEYMAP) --output $(KEYBOARD_OUTPUT)/src/build_json_rules.mk)
    include $(INFO_RULES_MK)

# Add rules to enerate the keymap files - indentation here is important
$(KEYBOARD_OUTPUT)/src/build_json_keymap.c: $(KEYMAP_JSON)
	bin/qmk json2c --quiet --output $(KEYMAP_C) $(KEYMAP_JSON)

$(KEYBOARD_OUTPUT)/src/build_json_config.h: $(KEYMAP_JSON)
	bin/qmk generate-config-h --quiet --keyboard $(KEYBOARD) --keymap $(KEYMAP) --output $(KEYBOARD_OUTPUT)/src/build_json_config.h

generated-files: $(KEYBOARD_OUTPUT)/src/build_json_config.h $(KEYBOARD_OUTPUT)/src/build_json_keymap.c

endif
