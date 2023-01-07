/* Copyright 2020 Alexander Dergachev (alexander.dergachev@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum torn_layers { _QWERTY, _LOWER, _RAISE, _ADJUST };

#define G_DEL LGUI_T(KC_DEL)
#define G_ENT RGUI_T(KC_ENT)

#define C_BSPC LCTL_T(KC_BSPC)
#define C_SPC RCTL_T(KC_SPC)

#define S_EQL LSFT_T(KC_EQL)
#define S_MINS RSFT_T(KC_MINS)

#define R_TAB LT(_RAISE, KC_TAB)
#define R_BSLS LT(_RAISE, KC_BSLS)

#define L_GRV LT(_LOWER, KC_GRV)
#define L_QUOT LT(_LOWER, KC_QUOT)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------.    ,-----------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * | Raise|      |      |      |      |      |    |      |      |      |      |      | Raise|
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | `    |   A  |   S  |   D  |   F  |   G  |    |   H  |   J  |   K  |   L  |   ;  |  '   |
 * | Lower|      |      |      |      |      |    |      |      |      |      |      | Lower|
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |  =+  |   Z  |   X  |   C  |   V  |   B  |    |   N  |   M  |   ,  |   .  |   /  |  -_  |
 * | Shift|      |      |      |      |      |    |      |      |      |      |      | Shift|
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 *               | ____ | Alt  | Bksp | Del  |    |Enter |Space | Alt  | ____ |
 *               |      |      | Ctrl | Gui  |    | Gui  | Ctrl |      |      |
 *               `---------------------------'    `---------------------------'
 */
[_QWERTY] = LAYOUT_split_3x6_4(
    R_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    R_BSLS,
    L_GRV,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, L_QUOT,
    S_EQL,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, S_MINS ,
                     _______, KC_LALT, C_BSPC,  G_DEL,     G_ENT,   C_SPC,   KC_RALT, _______
),

/* Lower
 * ,-----------------------------------------.    ,-----------------------------------------.
 * |  Esc |   !  |   @  |   #  |   $  |   %  |    |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |   [  |   ]  |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 *               | ____ | Alt  | Bksp | Del  |    |Enter |Space | Alt  | ____ |
 *               |      |      | Ctrl | Gui  |    | Gui  | Ctrl |      |      |
 *               `---------------------------'    `---------------------------'
 */
[_LOWER] = LAYOUT_split_3x6_4(
    KC_ESC,   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
    KC_TRNS,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
    KC_TRNS,  _______, _______, _______, _______, _______,   _______, _______, _______, KC_LBRC, KC_RBRC, KC_TRNS,
                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* Raise
 * ,-----------------------------------------.    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |    | S+H  | S+A+L|  UP  | S+A+R| S+E  |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  |  F10 |    | Home | Left | Down | Right| End  | PgUp |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |  F11 |  F12 |      |      |      |    | A+L  | S+L  | S+D  | S+R  | A+R  | PgDn |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 *               | ____ | Alt  | Bksp | Del  |    |Enter |Space | Alt  | ____ |
 *               |      |      | Ctrl | Gui  |    | Gui  | Ctrl |      |      |
 *               `---------------------------'    `---------------------------'
 */
[_RAISE] = LAYOUT_split_3x6_4(
    KC_TRNS, KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,     S(KC_HOME), S(A(KC_LEFT)), KC_UP,      S(A(KC_RGHT)), S(KC_END),  KC_TRNS,
    KC_TRNS, KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,    KC_HOME,    KC_LEFT,       KC_DOWN,    KC_RGHT,       KC_END,     KC_PGUP,
    KC_TRNS, KC_F11, KC_F12,  _______, _______, _______,   A(KC_LEFT), S(KC_LEFT),    S(KC_DOWN), S(KC_RGHT),    A(KC_RGHT), KC_PGDN ,
                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* Adjust
 * ,-----------------------------------------.    ,-----------------------------------------.
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 *               | ____ | Alt  | Bksp | Del  |    |Enter |Space | Alt  | ____ |
 *               |      |      | Ctrl | Gui  |    | Gui  | Ctrl |      |      |
 *               `---------------------------'    `---------------------------'
 */
[_ADJUST] = LAYOUT_split_3x6_4(
    _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
)

};

const uint16_t PROGMEM encoder_keymaps[][2][2] = {
    [_QWERTY] =  { { C(S(KC_TAB)), C(KC_TAB) },     { G(A(KC_LEFT)), G(A(KC_RIGHT)) } },
    [_LOWER]  =  { { C(KC_LEFT),   C(KC_RGHT) },    { KC_VOLD,       KC_VOLU } },
    [_RAISE]  =  { { G(KC_LEFT),   G(KC_RGHT) },    { G(KC_TAB),     G(S(KC_TAB)) } },
    [_ADJUST] =  { { KC_TRNS,      KC_TRNS },       { KC_TRNS,       KC_TRNS } },
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    torn_set_led(0, IS_LAYER_ON_STATE(state, _RAISE));
    torn_set_led(1, IS_LAYER_ON_STATE(state, _LOWER));
    torn_set_led(2, IS_LAYER_ON_STATE(state, _ADJUST));
    return state;
}

/*
 * Enable `IGNORE_MOD_TAP_INTERRUPT` for all modifiers except `Shift`.
 * For more info see `IGNORE_MOD_TAP_INTERRUPT_PER_KEY` in `docs/tap_hold.md`.
 */

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case S_EQL:
            return false;
        case S_MINS:
            return false;
        default:
            return true;
    }
}

/*
 * Enable `PERMISSIVE_HOLD` for `Shift` modifers.
 * For more info see `PERMISSIVE_HOLD_PER_KEY` in `docs/tap_hold.md`.
 */

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case S_EQL:
            return true;
        case S_MINS:
            return true;
        default:
            return false;
    }
}
