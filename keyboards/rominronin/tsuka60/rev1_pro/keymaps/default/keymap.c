// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ ` │ 1 │ 2 │ 3 │ 4 │ 5 │PgU│ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Tab│Cap│ Q │ W │ E │ R │ T │PgD│ Y │ U │ I │ O │ P │ [ │ ] │
     * ├───┴──┬┴──┬┴──┬┴──┬┴──┬┴──┬┴───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
     * │ Ctrl │ A │ S │ D │ F │ G │BkSpc│ H │ J │ K │ L │ ; │ Enter│
     * ├─────┬┴──┬┴──┬┴──┬┴──┬┴──┬┴──┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬─────┤
     * │Shift│ Z │ X │ C │ V │ B │Hom│End│ N │ M │ , │ . │ / │Shift│
     * ├───┬─┴─┬─┴─┬─┴─┬─┴──┬┴───┼───┼───┼───┴┬──┴─┬─┴─┬─┴─┬─┴─┬───┤
     * │Ctl│Ctl│Ctl│Win│Alt │ Sp │Ent│Ent│ Sp │Ctrl│ ← │ ↓ │ ↑ │ → │
     * └───┴───┴───┴───┴────┴────┴───┴───┴────┴────┴───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_PGUP, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
        KC_TAB,  KC_CAPS, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_PGDN, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
            KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_BSPC,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_HOME, KC_END,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
            KC_LCTL, KC_LCTL, KC_LCTL, KC_LGUI, KC_LALT, KC_SPACE,KC_ENT,  KC_ENT,  KC_SPACE,KC_RCTL, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
    )
};
