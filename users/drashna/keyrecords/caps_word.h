// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "drashna.h"

// Call this function from `process_record_user()` to implement Caps Word.
bool process_caps_word(uint16_t keycode, keyrecord_t* record);

// If CAPS_WORD_IDLE_TIMEOUT is set, call `caps_word_task()` from
// `matrix_scan_user()` as described above.
//
// If CAPS_WORD_IDLE_TIMEOUT isn't set, calling this function has no effect (but
// will still compile).
#if CAPS_WORD_IDLE_TIMEOUT > 0
void caps_word_task(void);
#else
static inline void caps_word_task(void) {}
#endif

// Activates or deactivates Caps Word. For instance activate Caps Word with a
// combo by defining a `COMBO_ACTION` that calls `caps_word_set(true)`:
//
// void process_combo_event(uint16_t combo_index, bool pressed) {
//   switch(combo_index) {
//     case CAPS_COMBO:
//       if (pressed) {
//         caps_word_set(true);  // Activate Caps Word.
//       }
//       break;
//
//     // Other combos...
//   }
// }
void caps_word_set(bool active);

// Returns whether Caps Word is currently active.
bool caps_word_get(void);

// An optional callback that gets called when Caps Word turns on or off. This is
// useful to represent the current Caps Word state, e.g. by setting an LED or
// playing a sound. In your keymap, define
//
//   void caps_word_set_user(bool active) {
//     if (active) {
//       // Do something when Caps Word activates.
//     } else {
//       // Do something when Caps Word deactivates.
//     }
//   }
void caps_word_set_user(bool active);

// An optional callback which is called on every key press while Caps Word is
// active. When the key should be shifted (that is, a letter key), the callback
// should call `add_weak_mods(MOD_BIT(KC_LSFT))` to shift the key. The callback
// also determines whether the key should continue Caps Word. Returning true
// continues the current "word", while returning false is "word breaking" and
// deactivates Caps Word. The default callback is
//
//   bool caps_word_press_user(uint16_t keycode) {
//     switch (keycode) {
//       // Keycodes that continue Caps Word, with shift applied.
//       case KC_A ... KC_Z:
//         add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
//         return true;
//
//       // Keycodes that continue Caps Word, without shifting.
//       case KC_1 ... KC_0:
//       case KC_BSPC:
//       case KC_MINS:
//       case KC_UNDS:
//         return true;
//
//       default:
//         return false;  // Deactivate Caps Word.
//     }
//   }
//
// To customize, copy the above function into your keymap and add/remove
// keycodes to the above cases.
//
// NOTE: Outside of this callback, you can use `caps_word_set(false)` to
// deactivate Caps Word.
bool caps_word_press_user(uint16_t keycode);
