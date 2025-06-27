// Copyright 2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifdef COMMUNITY_MODULE_CUSTOM_SHIFT_KEYS_ENABLE

uint16_t custom_shift_keys_count_raw(void) {
  return ARRAY_SIZE(custom_shift_keys);
}

__attribute__((weak)) uint16_t custom_shift_keys_count(void) {
  return custom_shift_keys_count_raw();
}

const custom_shift_key_t* custom_shift_keys_get_raw(uint16_t index) {
  if (index >= custom_shift_keys_count_raw()) {
    return NULL;
  }
  return &custom_shift_keys[index];
}

__attribute__((weak)) const custom_shift_key_t* custom_shift_keys_get(
    uint16_t index) {
  return custom_shift_keys_get_raw(index);
}

#endif // COMMUNITY_MODULE_CUSTOM_SHIFT_KEYS_ENABLE
