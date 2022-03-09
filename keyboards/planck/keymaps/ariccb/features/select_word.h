// Copyright 2021 Google LLC
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
// Select word/line button.
//
// Implements a button that selects the current word, assuming conventional text
// editor hotkeys. Pressing it again extends the selection to the following
// word. The effect is similar to word selection (W) in the Kakoune editor.
//
// Pressing the button with shift selects the current line, and pressing the
// button again extends the selection to the following line.
//
// Note for Mac users: Windows/Linux editing hotkeys are assumed by default.
// Uncomment the `#define MAC_HOTKEYS` line in select_word.c for Mac hotkeys.
// The Mac implementation is untested, let me know if it has problems.
//
// For full documentation, see
// https://getreuer.info/posts/keyboards/select-word

#pragma once

#include QMK_KEYBOARD_H

bool process_select_word(uint16_t keycode, keyrecord_t* record,
                         uint16_t sel_keycode);
