// Copyright 2021 Christoph Rehmann (crehmann)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD

// Using the right side as master
#define MASTER_RIGHT

#ifdef HAPTIC_ENABLE
// this configuration has no effect because the haptic exclusion is implemented with
// __attribute__((weak)) bool get_haptic_enabled_key(uint16_t keycode, keyrecord_t *record)
// in the default keymap and reacts only to mouse clicks. 
//#define NO_HAPTIC_MOD
#define NO_HAPTIC_FN
#define NO_HAPTIC_ALPHA
#define NO_HAPTIC_PUNCTUATION
#define NO_HAPTIC_NAV 
#define NO_HAPTIC_NUMERIC
#define DRV_GREETING       alert_750ms
#define DRV_MODE_DEFAULT   sharp_tick1
#endif


#ifdef PS2_MOUSE_ENABLE
#define PS2_MOUSE_SCROLL_BTN_MASK (1<<PS2_MOUSE_BTN_RIGHT)   // using the right mouse button for scrolling (other buttons can be configured)
#define PS2_MOUSE_SCROLL_BTN_SEND 500
#endif