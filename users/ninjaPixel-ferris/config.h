// Copyright 2025 ninjaPixel
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Shared configuration for the ninjaPixel Ferris Sweep keymap.
// QMK automatically includes this file when a keymap sets
// `USER_NAME := ninjaPixel-ferris` in its rules.mk.

#pragma once

// ──────────────────────────────────────────────────────────────
// Home-row mod tuning
//
// The base layer turns the eight home-row keys into Mod-Tap keys
// (e.g. LGUI_T(KC_A) = tap "a", hold = GUI/Cmd). Because the Ferris only
// has 34 keys there is nowhere else to put the modifiers comfortably, so
// these three settings are what make hold-vs-tap feel right while typing
// fast. If typing feels wrong, this is the first place to tweak.
// ──────────────────────────────────────────────────────────────

// How long (ms) a key must be held before it counts as a "hold" (the
// modifier/layer) instead of a "tap" (the letter). 200ms is a deliberately
// safe starting value that avoids accidental modifiers while typing. Lower it
// (e.g. 160ms) if the mods feel sluggish to trigger; raise it if you get a
// modifier when you only meant to type the letter.
#define TAPPING_TERM 200

// PERMISSIVE_HOLD: if you press *and release* another key while a Mod-Tap key
// is still held, resolve the Mod-Tap as a hold immediately (don't wait out the
// full tapping term). This makes fast modifier rolls such as "T then H" =
// Shift+H register reliably. Recommended for home-row mods.
#define PERMISSIVE_HOLD

// QUICK_TAP_TERM 0: disable "tap-then-hold = auto-repeat" for Mod-Tap keys.
// Without this, quickly tapping a key and then holding it again would repeat
// the letter (aaaa) instead of activating the hold. Setting it to 0 means a
// hold immediately after a tap is always treated as the hold action — the
// behaviour you want for home-row mods.
#define QUICK_TAP_TERM 0
