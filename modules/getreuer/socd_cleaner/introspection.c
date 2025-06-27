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

#ifdef COMMUNITY_MODULE_SOCD_CLEANER_ENABLE

uint16_t socd_opposing_pairs_count_raw(void) {
  return ARRAY_SIZE(socd_opposing_pairs);
}

__attribute__((weak)) uint16_t socd_opposing_pairs_count(void) {
  return socd_opposing_pairs_count_raw();
}

socd_cleaner_t* socd_opposing_pairs_get_raw(uint16_t index) {
  if (index >= socd_opposing_pairs_count_raw()) {
    return NULL;
  }
  return &socd_opposing_pairs[index];
}

__attribute__((weak)) socd_cleaner_t* socd_opposing_pairs_get(uint16_t index) {
  return socd_opposing_pairs_get_raw(index);
}

#endif // COMMUNITY_MODULE_SOCD_CLEANER_ENABLE
