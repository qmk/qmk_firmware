# Look for a json keymap file
ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_5)/keymap.json)","")
    -include $(MAIN_KEYMAP_PATH_5)/rules.mk
    KEYMAP_C := $(KEYBOARD_OUTPUT)/src/keymap.c
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_5)/keymap.json
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH_5)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_4)/keymap.json)","")
    -include $(MAIN_KEYMAP_PATH_4)/rules.mk
    KEYMAP_C := $(KEYBOARD_OUTPUT)/src/keymap.c
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_4)/keymap.json
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH_4)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_3)/keymap.json)","")
    -include $(MAIN_KEYMAP_PATH_3)/rules.mk
    KEYMAP_C := $(KEYBOARD_OUTPUT)/src/keymap.c
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_3)/keymap.json
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH_3)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_2)/keymap.json)","")
    -include $(MAIN_KEYMAP_PATH_2)/rules.mk
    KEYMAP_C := $(KEYBOARD_OUTPUT)/src/keymap.c
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_2)/keymap.json
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH_2)
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_1)/keymap.json)","")
    -include $(MAIN_KEYMAP_PATH_1)/rules.mk
    KEYMAP_C := $(KEYBOARD_OUTPUT)/src/keymap.c
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_1)/keymap.json
    KEYMAP_PATH := $(MAIN_KEYMAP_PATH_1)
endif

# Generate the keymap.c
$(KEYBOARD_OUTPUT)/src/keymap.c: $(KEYMAP_JSON)
	bin/qmk json2c --quiet --output $(KEYMAP_C) $(KEYMAP_JSON)
