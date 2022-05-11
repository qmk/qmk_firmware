// Copyright 2022 Kevin Goldberg @kevkevco <hello@kevkev.co>
// SPDX-License-Identifier: GPL-2.0-or-later
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

#include "quantum.h"

bool process_select_word(uint16_t keycode, keyrecord_t* record,
                         uint16_t sel_keycode);

