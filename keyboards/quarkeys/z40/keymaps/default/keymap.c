/*
/ Copyright 2022 quarkeys
/ This program is free software: you can redistribute it and/or modify
/ it under the terms of the GNU General Public License as published by
/ the Free Software Foundation, either version 2 of the License, or
/ (at your option) any later version.
/ This program is distributed in the hope that it will be useful,
/ but WITHOUT ANY WARRANTY; without even the implied warranty of
/ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/ GNU General Public License for more details.
/ You should have received a copy of the GNU General Public License
/ along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* [0]
     * ,-------------------------------------------------------------------------------------.
     * | Esc   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  BS   |
     * |------------+------+------+------+------+-------------+------+------+------+------+--|
     * | Tab   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "    |
     * |------------+------+------+------+------+------|------+------+------+------+------+--|
     * | SHIFT |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift |
     * |-------+-------+-------+-------+-------+-------+------+------+------+------+------+--|
     * | Ctrl  | Caps |  ALT |  OS  | Ly1  |    SPACE    | Ly2  |  M1  |  M2  |  M3  | Enter |
     * `-------------------------------------------------------------------------------------'
     */
    [0] = LAYOUT_planck_mit(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_CAPS, KC_LALT, KC_LGUI, MO(1),       KC_SPC,       MO(2),   MO(3),   _______, _______, KC_ENT
    ),

    /* [1]
     * ,-------------------------------------------------------------------------------------.
     * | Reset | PgUp | Home |  Up  |  End |  Del |   \  |  7   |  8   |   9  | RGBtg |  BS  |
     * |-------+------+------+------+------+------+------+------+------+------+-------+------|
     * |       | PgDn | Left | Down | Rght |   +  |   -  |  4   |  5   |   6  | RGBmod|      |
     * |-------+------+------+------+------+------+------+------+------+------+-------+------|
     * |       | Vol- | Vol+ | Play | Mute |   *  |   /  |  1   |  2   |   3  |   /   |      |
     * |-------+------+------+------+------+------+------+------+------+------+-------+------|
     * |       |      |      |      |      |      0      |      |      |   .  |       |  =   |
     * `-------+------+------+------+------+-------------+------+------+------+-------+------'
     */
    [1] = LAYOUT_planck_mit(
        QK_BOOT, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,  KC_BSLS, KC_7,    KC_8,    KC_9,    RM_TOGG, _______,
        _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PLUS, KC_MINS, KC_4,    KC_5,    KC_6,    RM_NEXT, _______,
        _______, KC_VOLD, KC_VOLU, _______, _______, KC_ASTR, KC_SLSH, KC_1,    KC_2,    KC_3,    RM_HUEU, _______,
        RM_SATU, RM_SATD, RM_VALU, RM_VALD, _______,     KC_0,         _______, _______, KC_DOT,  RM_HUED, KC_EQL
    ),

    /* [2]
     * ,-------------------------------------------------------------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11  |  F12  |
     * |------+------+------+------+------+------+------+------+------+------+----+--+-------|
     * |      |  &   |  |   |  (   |  )   |      |      |  {   |  }   |  [   |  ]    |       |
     * |------+------+------+------+------+------+------+------+------+------+-------+-------|
     * |      |  !   |  @   |  #   |  ^   |      |      |  ~   |  <   |  >   |  ?    |       |
     * |------+------+------+------+------+------+------+------+------+------+-------+-------|
     * |      |      |      |      |      |             |      |      |      |       |       |
     * `-------------------------------------------------------------------------------------'
     */
    [2] = LAYOUT_planck_mit(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        _______, KC_AMPR, KC_PIPE, KC_LPRN, KC_RPRN, KC_PLUS, KC_MINS, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, _______,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_CIRC, KC_ASTR, KC_SLSH, KC_TILD, KC_LABK, KC_RABK, KC_QUES, _______,
        _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
    )
};

#ifdef RGBLIGHT_ENABLE
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({9, 1, HSV_RED});
const rgblight_segment_t PROGMEM my_ar_numpad_layer[] = RGBLIGHT_LAYER_SEGMENTS({40, 2, HSV_WHITE});
const rgblight_segment_t PROGMEM my_symbol_layer[] = RGBLIGHT_LAYER_SEGMENTS({28, 2, HSV_WHITE});
const rgblight_segment_t PROGMEM my_other_layer[] = RGBLIGHT_LAYER_SEGMENTS({16, 2, HSV_WHITE});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,        // Caplock indicator
    my_ar_numpad_layer,        // Arrow keys & Numpad, Operator keys, reset key, RGB control and media control
    my_symbol_layer,        // F1-F12 keys & Symbols
    my_other_layer            // Self-Defined
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    return state;
}
#endif
