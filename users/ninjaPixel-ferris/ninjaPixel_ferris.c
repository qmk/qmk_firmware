// Copyright 2025 ninjaPixel
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Shared callbacks for the ninjaPixel Ferris Sweep keymap.
//
// This file is the home for keyboard-wide behaviour that can't be expressed as
// plain keycodes in the layer tables — for example custom keycodes / macros,
// layer-switching logic, or (if you ever add a display) OLED rendering.
//
// The keymap data itself (the `keymaps` array) deliberately lives in
// ninjaPixel_ferris_keymap.h, which is included directly from the board's
// keymap.c. QMK's introspection has to see that array inside the keymap
// compilation unit, which is why it is a header rather than part of this file.

#include "ninjaPixel_ferris.h"

// ──────────────────────────────────────────────────────────────
// Custom keycode handling
//
// Right now there are no custom keycodes — every key in the layout is a stock
// QMK keycode — so this callback simply returns true, letting QMK process every
// press normally. It is included as a ready-made hook: when you want a macro or
// other custom behaviour, add a custom keycode to an enum in
// ninjaPixel_ferris.h (starting at SAFE_RANGE), place it in a layer, and handle
// it in the switch below. Return false from a case to tell QMK that you have
// fully handled that keypress and it should do nothing further.
// ──────────────────────────────────────────────────────────────
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Example macro, left here (commented out) as a template:
        // case NP_EMAIL:
        //     if (record->event.pressed) {
        //         SEND_STRING("me@example.io");
        //     }
        //     return false; // handled here; QMK should do nothing else

        default:
            return true; // not a custom keycode — let QMK handle it normally
    }
}
