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

#include "test_keymap.h"
#include "quantum.h"

// clang-format off
const keycode_string_name_t keycode_string_names_kb[] = {
    KEYCODE_STRING_NAME(MYMACRO1),
};

const keycode_string_name_t keycode_string_names_user[] = {
    KEYCODE_STRING_NAME(MYMACRO2),
    KEYCODE_STRING_NAME(KC_EXLM),
};
// clang-format on
