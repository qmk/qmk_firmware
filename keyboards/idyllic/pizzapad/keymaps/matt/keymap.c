// Copyright 2024 Matt (@matt)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Pizza Pad (Pretty Paddy) — Window Management Keymap
//
// Layout:
//   [K0] [K1] [K2]
//   [K3] [K4] [K5]
//   [K6] [K7] [K8]
//
// All edge keys are LT() (Layer-Tap): tap fires a window command,
// hold activates an anchor layer for chording.
//
// Corner keys (K0/K2/K6/K8) cannot use HYPR(KC_x) directly inside LT()
// because HYPR(KC_x) is a modified keycode and LT() only accepts basic
// keycodes as the tap action. Instead, placeholder F-keys are used and
// intercepted in process_record_user() to emit the correct HYPR+num.
//
//   K0 → placeholder KC_F22 → intercepted → HYPR+1
//   K2 → placeholder KC_F23 → intercepted → HYPR+3
//   K6 → placeholder KC_F24 → intercepted → HYPR+7
//   K8 → placeholder KC_SCRL → intercepted → HYPR+9  (scroll lock; macOS ignores it)
//
// Layer 0 (Base):
//   K0: tap=HYPR+1,   hold=_TOP_HOLD
//   K1: tap=HYPR+2    (plain, no hold)
//   K2: tap=HYPR+3,   hold=_TOP_HOLD
//   K3: tap=F18,      hold=_LEFT_HOLD
//   K4: tap=HYPR+5    (plain, no hold)
//   K5: tap=F19,      hold=_RIGHT_HOLD
//   K6: tap=HYPR+7,   hold=_BOT_HOLD
//   K7: tap=HYPR+8    (plain, no hold)
//   K8: tap=HYPR+9,   hold=_BOT_HOLD
//
// Layer 1 (_LEFT_HOLD — hold K3):
//   K3+K1 → HYPR+0       (Top Half)
//   K3+K4 → F13          (Left Two-Thirds)
//   K3+K5 → HYPR+Return  (Full Screen)
//   K3+K7 → F16          (Bottom Half)
//
// Layer 2 (_RIGHT_HOLD — hold K5):
//   K5+K3 → HYPR+Return  (Full Screen)
//   K5+K4 → F20          (Right Two-Thirds)
//
// Layer 3 (_TOP_HOLD — hold K0 or K2, shared layer):
//   K0+K2 → HYPR+0       (Top Half)
//   K2+K0 → HYPR+0       (Top Half)
//
// Layer 4 (_BOT_HOLD — hold K6 or K8, shared layer):
//   K6+K8 → F16          (Bottom Half)
//   K8+K6 → F16          (Bottom Half)
//
// Avoided F-keys: F14 (brightness down), F15 (brightness up), F17 (brightness).
// F21+ not recognised by Raycast as recordable hotkeys.

#include QMK_KEYBOARD_H

enum custom_layers {
    _BASE = 0,
    _LEFT_HOLD,
    _RIGHT_HOLD,
    _TOP_HOLD,        // shared by K0 and K2 — same pattern as _BOT_HOLD for K6/K8
    _BOT_HOLD         // shared by K6 and K8
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_ortho_3x3(
        LT(_TOP_HOLD,   KC_F22),   HYPR(KC_2),   LT(_TOP_HOLD,   KC_F23),
        LT(_LEFT_HOLD,      KC_F18),   HYPR(KC_5),                   LT(_RIGHT_HOLD,     KC_F19),
        LT(_BOT_HOLD,       KC_F24),   HYPR(KC_8),   LT(_BOT_HOLD,       KC_SCRL)
    ),

    // Hold K3
    [_LEFT_HOLD] = LAYOUT_ortho_3x3(
        KC_TRNS,       HYPR(KC_0),        KC_TRNS,
        KC_TRNS,       KC_F13,        HYPR(KC_ENT),
        KC_TRNS,       KC_F16,        KC_TRNS
    ),

    // Hold K5
    [_RIGHT_HOLD] = LAYOUT_ortho_3x3(
        KC_TRNS,       KC_TRNS,       KC_TRNS,
        HYPR(KC_ENT),  KC_F20,        KC_TRNS,
        KC_TRNS,       KC_TRNS,       KC_TRNS
    ),

    // Shared by K0 and K2 — same pattern as _BOT_HOLD
    // Both positions have HYPR(KC_0) so either key can be the anchor
    [_TOP_HOLD] = LAYOUT_ortho_3x3(
        HYPR(KC_0),        KC_TRNS,       HYPR(KC_0),
        KC_TRNS,       KC_TRNS,       KC_TRNS,
        KC_TRNS,       KC_TRNS,       KC_TRNS
    ),

    // Hold K6 or K8 — both positions send F16 so either can be the anchor
    [_BOT_HOLD] = LAYOUT_ortho_3x3(
        KC_TRNS,          KC_TRNS,       KC_TRNS,
        KC_TRNS,          KC_TRNS,       KC_TRNS,
        KC_F16,           KC_TRNS,       KC_F16
    ),

};

// Intercept placeholder taps on corner keys and send the correct HYPR+num.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_TOP_HOLD, KC_F22):             // K0 tap → HYPR+1
            if (record->tap.count && record->event.pressed) {
                tap_code16(HYPR(KC_1));
                return false;
            }
            break;
        case LT(_TOP_HOLD, KC_F23):             // K2 tap → HYPR+3
            if (record->tap.count && record->event.pressed) {
                tap_code16(HYPR(KC_3));
                return false;
            }
            break;
        case LT(_BOT_HOLD, KC_F24):             // K6 tap → HYPR+7
            if (record->tap.count && record->event.pressed) {
                tap_code16(HYPR(KC_7));
                return false;
            }
            break;
        case LT(_BOT_HOLD, KC_SCRL):            // K8 tap → HYPR+9
            if (record->tap.count && record->event.pressed) {
                tap_code16(HYPR(KC_9));
                return false;
            }
            break;
    }
    return true;
}
