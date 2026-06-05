// Copyright 2025 ninjaPixel
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Shared header for the ninjaPixel Ferris Sweep keymap.
// Declares the layer enum, which is used both by the keymap data
// (ninjaPixel_ferris_keymap.h) and by the shared callbacks
// (ninjaPixel_ferris.c).

#pragma once

#include QMK_KEYBOARD_H

// ──────────────────────────────────────────────────────────────
// Layer indices
//
// The Ferris Sweep has only 34 keys, so everything beyond the base alphas
// lives on a hold-activated layer. Naming the layers (rather than using bare
// numbers like [0], [1], ...) keeps the keymap readable and makes inserting or
// reordering layers painless.
//
// Every non-base layer is reached by holding a thumb key on the BASE layer
// (see the LAYOUT comments in ninjaPixel_ferris_keymap.h):
//   _NAV  ← hold the LEFT  inner thumb  (LT(_NAV, KC_SPC))
//   _SYM  ← hold the RIGHT inner thumb  (LT(_SYM, KC_BSPC))
//   _FN   ← hold the LEFT  outer thumb  (LT(_FN,  KC_ESC))
// ──────────────────────────────────────────────────────────────
enum ferris_layers {
    _BASE, // 0: Colemak-DH alphas with home-row mods
    _NAV,  // 1: number row + arrow / navigation cluster
    _SYM,  // 2: symbols
    _FN,   // 3: function keys, media, volume, and keyboard control
};
