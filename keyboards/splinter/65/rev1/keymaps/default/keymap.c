// Copyright 2025 Konstantin Goncharuk
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/* Each layer gets a name for readability */
enum layer_names { _BASE, _FN };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(KC_ESC,    KC_1,    KC_2,      KC_3,   KC_4,   KC_5,   KC_6,           KC_7,   KC_8,   KC_9,    KC_0,      KC_MINS,    KC_EQL,     KC_BSPC,
                     KC_TAB,    KC_Q,    KC_W,      KC_E,   KC_R,   KC_T,   KC_NO,          KC_Y,   KC_U,   KC_I,    KC_O,      KC_P,       KC_LBRC,    KC_RBRC,
                     KC_CAPS,   KC_A,    KC_S,      KC_D,   KC_F,   KC_G,   KC_NO,          KC_H,   KC_J,   KC_K,    KC_L,      KC_SCLN,    KC_QUOT,    KC_BSLS,
                     KC_LSFT,   KC_GRV,  KC_Z,      KC_X,   KC_C,   KC_V,   KC_B,           KC_N,   KC_M,   KC_COMM, KC_DOT,    KC_SLSH,    KC_UP,      KC_DEL,
                     KC_LCTL,   KC_LALT, KC_LGUI,   KC_SPC, KC_NO,  KC_NO,  MO(_FN),        KC_SPC, MO(_FN),KC_HOME, KC_LEFT,   KC_DOWN,    KC_RIGHT,   KC_ENT),

    /* FN - Function keys and navigation */
    [_FN] = LAYOUT(XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,   KC_F9,        KC_F10,            KC_F11,       KC_F12,         XXXXXXX,
                   XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_HOME, KC_END,  XXXXXXX,       XXXXXXX, KC_UP,   KC_DEL,       XXXXXXX,           XXXXXXX,      XXXXXXX,        XXXXXXX,
                   XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, KC_LEFT, KC_DOWN,      KC_RIGHT,          XXXXXXX,      XXXXXXX,        XXXXXXX,
                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,           XXXXXXX,      XXXXXXX,        XXXXXXX,
                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX,      KC_VOLD,           KC_MUTE,      KC_VOLU,        XXXXXXX)
};
