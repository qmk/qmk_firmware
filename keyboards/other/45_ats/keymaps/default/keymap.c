 /* 
 Copyright 2020 Alec Penland
 Copyright 2020 Garret Gartner
  
 This program is free software: you can redistribute it and/or modify 
 it under the terms of the GNU General Public License as published by 
 the Free Software Foundation, either version 2 of the License, or 
 (at your option) any later version. 
  
 This program is distributed in the hope that it will be useful, 
 but WITHOUT ANY WARRANTY; without even the implied warranty of 
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 GNU General Public License for more details. 
  
 You should have received a copy of the GNU General Public License 
 along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */ 

#include QMK_KEYBOARD_H

// Layer names
enum ats_layers{
  // - Base layer:
  _BASE,
  // - Symbols, numbers, and functions:
  _FN,
  // - Alternate Function layer:
  _LN
};

#define RS_SLS RSFT_T(KC_SLSH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Default QWERTY layer 
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐   ┌───┐
     * │Esc│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │Del│BkS│   │PgU│
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤   ├───┤
     * │Tab │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ' │Enter │   │PgD│
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬───┘   ├───┤
     * │LShift│ Z │ X │ C │ V │ B │ N │ M │ , │ . │Sft/│ ┌───┐ │CAP│
     * ├────┬─┴─┬─┴──┬┴───┴───┴─┬─┴───┴──┬┴───┼───┴┬───┘ │ ↑ │ └───┘
     * │LCtl│OS │LAlt│    Fn    │  Space │RAlt│ Ln │ ┌───┼───┼───┐
     * └────┴───┴────┴──────────┴────────┴────┴────┘ │ ← │ ↓ │ → │
     *                                               └───┴───┴───┘
     */
    [_BASE] = LAYOUT_split_space(
        KC_ESC,   KC_Q,     KC_W,    KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,     KC_O,    KC_P,      KC_DEL, KC_BSPC,         KC_PGUP,
        KC_TAB,   KC_A,     KC_S,    KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,     KC_L,    KC_QUOTE,      KC_ENT,              KC_PGDN,
        KC_LSFT,  KC_Z,     KC_X,    KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM,  KC_DOT,  RS_SLS,                 KC_UP,      KC_CAPS,
        KC_LCTL,  KC_LGUI,  KC_LALT,          MO(_FN),      KC_SPACE,        KC_RALT,      MO(_LN),       KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    /* Main Numbers, Symbols & Function Layer (MOMENTARY)
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐   ┌───┐
     * │   │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ [ │ ] │ \ │   │   │Hme│
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤   ├───┤
     * │    │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │      │   │End│
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬───┘   ├───┤
     * │      │ ( │ ) │ ; │ . │   │ - │ + │ * │ / │ =  │ ┌───┐ │   │
     * ├────┬─┴─┬─┴──┬┴───┴───┴─┬─┴───┴──┬┴───┼───┴┬───┘ │   │ └───┘
     * │    │   │    │          │        │    │    │ ┌───┼───┼───┐
     * └────┴───┴────┴──────────┴────────┴────┴────┘ │   │   │   │
     *                                               └───┴───┴───┘
     */
    [_FN] = LAYOUT_split_space(
        _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,  KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LBRC,  KC_RBRC,  KC_BSLS,   _______,             KC_HOME,
        _______,  KC_1,     KC_2,     KC_3,     KC_4,    KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,          KC_ENTER,                  KC_END,
        _______,  KC_LPRN,  KC_RPRN,  KC_SCLN,  KC_DOT,  _______,  KC_MINS,  KC_PLUS,  KC_ASTR,  KC_SLSH,  KC_EQL,                     _______,      _______,
        _______,  _______,  _______,                _______,            _______,            _______,       _______,          _______,  _______,   _______
    ),

    /* ALTERNATE Function layer (MOMENTARY)
     * ┌────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐   ┌───┐
     * │ PWR│F1 │F2 │F3 │F4 │F5 │F6 │   │   │   │   │PRV│NXT│   │VL+│
     * ├────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤   ├───┤
     * │ SLP │F7 │F8 │F9 │F10│F11│F12│   │   │   │   │ PLAY │   │VL-│
     * ├─────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬───┘   ├───┤
     * │ WAKE  │   │   │   │   │   │   │   │   │   │    │ ┌───┐ │   │
     * ├────┬──┴─┬─┴──┬┴───┴───┴─┬─┴───┴──┬┴───┼───┴┬───┘ │   │ └───┘
     * │RSET│    │    │          │        │    │    │ ┌───┼───┼───┐
     * └────┴────┴────┴──────────┴────────┴────┴────┘ │   │   │   │
     *                                                └───┴───┴───┘
     */
    [_LN] = LAYOUT_split_space(
        KC_PWR,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    _______,  _______,  _______,  _______,  KC_MPRV,  KC_MNXT,               KC_VOLU,
        KC_SLEP,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,  _______,       KC_MPLY,                    KC_VOLD,
        KC_WAKE,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                    _______,       _______,
        RESET,    _______,  _______,                 _______,            _______,            _______,       _______,          _______,  _______,   _______
    )
};

//function for layer indicator LED
layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(D0, layer_state_cmp(state, 0));
    writePin(D1, layer_state_cmp(state, 1));
    writePin(D2, layer_state_cmp(state, 2));
    return state;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
