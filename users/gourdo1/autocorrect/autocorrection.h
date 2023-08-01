// Copyright 2021-2022 Google LLC
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
//
//
// Autocorrection on your keyboard.
//
// This library implements rudimentary autocorrection, automatically detecting
// and fixing some misspellings. Beware that the autocorrection logic is
// unaware of hotkey or mouse-based cursor movement.
//
// For full documentation, see
// https://getreuer.info/posts/keyboards/autocorrection

#pragma once

#include "quantum.h"

#include "gourdo1.h"

#ifdef __cplusplus
extern "C" {
#endif

bool process_autocorrection(uint16_t keycode, keyrecord_t* record);

#ifdef __cplusplus
}
#endif

