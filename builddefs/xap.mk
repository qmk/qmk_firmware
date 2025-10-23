# Copyright 2022 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later

XAP_FILES := $(shell ls -1 data/xap/* | sort | xargs echo)
ifneq ("$(wildcard $(KEYBOARD_PATH_1)/xap.hjson)","")
	XAP_FILES += $(KEYBOARD_PATH_1)/xap.hjson
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_2)/xap.hjson)","")
	XAP_FILES += $(KEYBOARD_PATH_2)/xap.hjson
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_3)/xap.hjson)","")
	XAP_FILES += $(KEYBOARD_PATH_3)/xap.hjson
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_4)/xap.hjson)","")
	XAP_FILES += $(KEYBOARD_PATH_4)/xap.hjson
endif
ifneq ("$(wildcard $(KEYBOARD_PATH_5)/xap.hjson)","")
	XAP_FILES += $(KEYBOARD_PATH_5)/xap.hjson
endif
ifneq ("$(wildcard $(KEYMAP_PATH)/xap.hjson)","")
	XAP_FILES += $(KEYMAP_PATH)/xap.hjson
endif
ifneq ("$(wildcard $(USER_NAME)/xap.hjson)","")
	XAP_FILES += $(USER_NAME)/xap.hjson
endif

$(INTERMEDIATE_OUTPUT)/src/config_blob_gz.h: $(INFO_JSON_FILES)
	@$(SILENT) || printf "$(MSG_GENERATING) $@" | $(AWK_CMD)
	$(eval CMD=$(QMK_BIN) xap-generate-qmk-blob-h -o "$(INTERMEDIATE_OUTPUT)/src/config_blob_gz.h" -kb $(KEYBOARD) -km $(KEYMAP))
	@$(BUILD_CMD)

$(INTERMEDIATE_OUTPUT)/src/xap_generated.inl: $(XAP_FILES)
	@$(SILENT) || printf "$(MSG_GENERATING) $@" | $(AWK_CMD)
	$(eval CMD=$(QMK_BIN) xap-generate-qmk-inc -o "$(INTERMEDIATE_OUTPUT)/src/xap_generated.inl" -kb $(KEYBOARD) -km $(KEYMAP))
	@$(BUILD_CMD)

$(INTERMEDIATE_OUTPUT)/src/xap_generated.h: $(XAP_FILES)
	@$(SILENT) || printf "$(MSG_GENERATING) $@" | $(AWK_CMD)
	$(eval CMD=$(QMK_BIN) xap-generate-qmk-h -o "$(INTERMEDIATE_OUTPUT)/src/xap_generated.h" -kb $(KEYBOARD) -km $(KEYMAP))
	@$(BUILD_CMD)

generated-files: $(INTERMEDIATE_OUTPUT)/src/config_blob_gz.h $(INTERMEDIATE_OUTPUT)/src/xap_generated.inl $(INTERMEDIATE_OUTPUT)/src/xap_generated.h

VPATH += $(INTERMEDIATE_OUTPUT)/src
