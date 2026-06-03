// Copyright 2024 SM Boards (@sm_boards)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Short, human-readable labels for QMK keycodes — used by the OLED to flash
// the name of whatever key (or encoder direction) was just triggered.
//
// Categories handled:
//   - Basic keys              KC_A..KC_Z, KC_0..KC_9, F-keys, navigation,
//                              editing, media, mouse, system, punctuation
//   - Modifier-wrapped        LCTL(KC_C)        -> "C+C"
//                              LCTL(LSFT(KC_X)) -> "C+S+X"
//   - Mod-tap                 LCTL_T(KC_A)      -> "C/A"
//   - Layer-tap               LT(2, KC_X)       -> "L2/X"
//   - Layer switches          MO(1)/TO/TG/TT/DF/OSL -> "MO1" etc.
//   - One-shot mods           OSM(MOD_LCTL)     -> "OSC"
//
// Anything not recognised falls back to a 4-digit hex dump ("0x1234") so the
// user still sees *something* meaningful.
//
// Custom user keycodes (QK_USER_*): a keymap can override keycode_label_user()
// (declared below, weak default returns NULL) to label them. The shared
// keycode_label() checks that hook first and returns its value if non-NULL.
//
// IMPORTANT: returned pointers reference STATIC storage that is REUSED on the
// next call. Copy the string immediately if the caller needs to keep it.

#pragma once

#include <stdint.h>

// Maximum label length the function may return, in characters (excluding the
// NUL terminator). Big-font glyphs are 12 px each; 10 chars * 12 = 120 px,
// which fits the 128 px wide OLED with a small left/right margin.
#define KEYCODE_LABEL_MAX 10

// Returns a short human-readable label for `kc`. Never returns NULL.
const char *keycode_label(uint16_t kc);

// Optional keymap-level hook for custom keycodes (QK_USER_0..). Define this
// in your keymap to label custom keycodes; return NULL for keycodes you don't
// recognise. The default (weak) implementation just returns NULL.
const char *keycode_label_user(uint16_t kc);
