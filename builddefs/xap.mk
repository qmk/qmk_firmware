# Copyright 2022 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later

# XAP embedded info.json
$(KEYMAP_OUTPUT)/src/info_json_gz.h: $(INFO_JSON_FILES)
	@$(SILENT) || printf "$(MSG_GENERATING) $@" | $(AWK_CMD)
	mkdir -p $(KEYMAP_OUTPUT)/src
	$(eval CMD=$(QMK_BIN) info -f json -kb $(KEYBOARD) -km $(KEYMAP) | gzip -c9 > $(KEYMAP_OUTPUT)/src/info.json.gz \
		&& cd $(KEYMAP_OUTPUT)/src >/dev/null 2>&1 \
		&& xxd -i info.json.gz info_json_gz.h \
		&& cd - >/dev/null 2>&1)
	@$(BUILD_CMD)

XAP_FILES := $(shell ls -1 data/xap/* | sort | xargs echo)

$(KEYMAP_OUTPUT)/src/xap_generated.inl: $(XAP_FILES)
	@$(SILENT) || printf "$(MSG_GENERATING) $@" | $(AWK_CMD)
	$(eval CMD=$(QMK_BIN) xap-generate-qmk-inc -o "$(KEYMAP_OUTPUT)/src/xap_generated.inl")
	@$(BUILD_CMD)

$(KEYMAP_OUTPUT)/src/xap_generated.h: $(XAP_FILES)
	@$(SILENT) || printf "$(MSG_GENERATING) $@" | $(AWK_CMD)
	$(eval CMD=$(QMK_BIN) xap-generate-qmk-h -o "$(KEYMAP_OUTPUT)/src/xap_generated.h" -kb $(KEYBOARD))
	@$(BUILD_CMD)

generated-files: $(KEYMAP_OUTPUT)/src/info_json_gz.h $(KEYMAP_OUTPUT)/src/xap_generated.inl $(KEYMAP_OUTPUT)/src/xap_generated.h

VPATH += $(KEYMAP_OUTPUT)/src
