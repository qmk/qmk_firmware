// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    BASE,  // default layer
    MDIA,  // media keys
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | CAPS |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCTL | LALT | LCMD | LGUI | /Enter  /       \Space \  | RGUI | DEL  | RALT | RCTL |
 *            |      |      |      |  LT1 |/       /         \      \ | LT1  |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[BASE] = LAYOUT_split_4x6_5(
    KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,     KC_7,     KC_8,    KC_9,    KC_0,    KC_GRV,
    KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                           KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_CAPS,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                           KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,   KC_MPLY,    KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                 KC_LCTL, KC_LALT, KC_LCMD, LT(MDIA,KC_LGUI), KC_ENT,  KC_SPC, LT(MDIA,KC_RGUI),  KC_DEL,  KC_RALT, KC_RCTL
),
[MDIA] = LAYOUT_split_4x6_5(
    KC_MUTE,_______,_______,_______,_______,_______,                           _______,_______,_______,_______,_______,_______,
    RM_TOGG,_______,_______,_______,_______,_______,                           _______,_______,_______,_______,_______,_______,
    RM_NEXT,_______,_______,_______,_______,_______,                           _______,_______,_______,_______,_______,_______,
    RM_HUEU,_______,_______,_______,_______,_______,   _______,     _______,   _______,_______,_______,_______,_______,_______,
                    _______,_______,_______,_______,   _______,     _______,   _______,_______,_______,_______
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [MDIA] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) }
};
#endif
