// Copyright 2022 Ulrich Spörlein (@uqs)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_MAX_LAYERS 8      // default is 16
#    define RGBLIGHT_DISABLE_KEYCODES  // RGB_foo keys no longer work, saves 600 bytes
#    define RGBLIGHT_DEFAULT_HUE 15
#endif

#define DYNAMIC_KEYMAP_LAYER_COUNT 6  // default is 4 for VIA builds

#define TAPPING_TOGGLE 2  // number of taps for a toggle-on-tap
#define TAPPING_TERM 170  // ms to trigger tap
// https://precondition.github.io/home-row-mods
#define QUICK_TAP_TERM 0  // make tap-then-hold _not_ do key auto repeat
#define PERMISSIVE_HOLD  // I don't think this works for me, hence I rolled my own implementation.

#define LEADER_TIMEOUT 400
#define LEADER_PER_KEY_TIMING

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX

// make KC_ACL0 et al work when held.
#define MK_COMBINED
#define MOUSEKEY_WHEEL_INTERVAL 40  // default is 50, lower means more scroll events, 40 works ok.

// From https://michael.stapelberg.ch/posts/2021-05-08-keyboard-input-latency-qmk-kinesis/
#define USB_POLLING_INTERVAL_MS 1

#ifdef KEYBOARD_preonic_rev3
// Some games seem to not register Esc otherwise when tapped, maybe try with this delay?
#    define TAP_CODE_DELAY 30
#else
#    define TAP_CODE_DELAY 10
#endif
