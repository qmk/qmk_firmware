# Copyright 2026 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Scan for community module unit tests.
MODULE_TEST_LIST = $(sort $(patsubst %/test.mk,%, $(shell find $(ROOT_DIR)modules -path '*/tests/*/test.mk' -type f 2>/dev/null)))
ifneq ($(strip $(QMK_USERSPACE)),)
    USERSPACE_MODULE_TEST_LIST = $(sort $(patsubst %/test.mk,%, $(shell find $(QMK_USERSPACE)/modules -path '*/tests/*/test.mk' -type f 2>/dev/null)))
    MODULE_TEST_LIST += $(USERSPACE_MODULE_TEST_LIST)
endif

# Append paths to test discovery list.
TEST_LIST += $(MODULE_TEST_LIST)
# Append dynamic target names to full tests list.
FULL_TESTS += $(foreach TEST,$(MODULE_TEST_LIST),$(call GET_TEST_INTERNAL_NAME,$(TEST)))

