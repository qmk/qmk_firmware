// Copyright 2025 ninjaPixel
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Shared configuration for all ninjaPixel keyboards.
// Settings here apply to both mechboards/sofle/pro and sofle/rev1.

#pragma once

// How long (in milliseconds) a key must be held before it is considered a
// "hold" rather than a "tap". This affects all Mod-Tap (MT) and Layer-Tap (LT)
// keys in the keymap.
//
// The main motivation for lowering this from the QMK default of 200ms is the
// MT(MOD_RSFT, KC_ENT) thumb key: when typing quickly, a fast press was often
// resolved as a tap (Enter) instead of a hold (Shift). Reducing the tapping
// term means QMK decides "hold" sooner, so Shift registers more reliably.
//
// 150ms is a reasonable starting point — lower it further (e.g. 120ms) if
// you still get accidental Enter presses, or raise it if you find Shift
// activating when you only meant to press Enter.
#define TAPPING_TERM 150
