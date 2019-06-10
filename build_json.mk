# Look for a json keymap file
ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_5)/keymap.json)","")
    KEYMAP_C := $(MAIN_KEYMAP_PATH_5)/keymap.c
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_5)/keymap.json
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_4)/keymap.json)","")
    KEYMAP_C := $(MAIN_KEYMAP_PATH_4)/keymap.c
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_4)/keymap.json
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_3)/keymap.json)","")
    KEYMAP_C := $(MAIN_KEYMAP_PATH_3)/keymap.c
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_3)/keymap.json
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_2)/keymap.json)","")
    KEYMAP_C := $(MAIN_KEYMAP_PATH_2)/keymap.c
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_2)/keymap.json
else ifneq ("$(wildcard $(MAIN_KEYMAP_PATH_1)/keymap.json)","")
    KEYMAP_C := $(MAIN_KEYMAP_PATH_1)/keymap.c
    KEYMAP_JSON := $(MAIN_KEYMAP_PATH_1)/keymap.json
endif

# Generate the keymap.c
ifneq ("$(KEYMAP_JSON)","")
    _ = $(shell bin/qmk-json-keymap -f $(KEYMAP_JSON) -o $(KEYMAP_C))
endif
