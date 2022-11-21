/*
Copyright 2020 Oliver Gaskell <me@gaskell.tech>

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

enum layers {
    _QWERTY = 0,
    _NUMPAD,
    _LOWER,
    _RAISE,
    _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_ortho_4x12(
        KC_MUTE, KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,   KC_Y,   KC_U,       KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,       KC_G,   KC_H,   KC_J,       KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,   KC_N,   KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        KC_BSPC, KC_LCTL, KC_LGUI, KC_LALT, MO(_LOWER), KC_SPC, KC_SPC, MO(_RAISE), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT),

    [_NUMPAD] = LAYOUT_ortho_4x12(
        KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P7, KC_P8,   KC_P9,   KC_PSLS,
        KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P4, KC_P5,   KC_P6,   KC_PAST,
        KC_TRNS, TG(_NUMPAD), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P1, KC_P2,   KC_P3,   KC_PENT,
        KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_PDOT, KC_PMNS, KC_PPLS),

    [_LOWER] = LAYOUT_ortho_4x12(
        KC_VOLD, KC_EXLM,       KC_AT,    KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,      KC_RPRN,       KC_INS,
        KC_NLCK, KC_F7,         KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_LCBR, KC_RCBR, KC_UNDS,      KC_PLUS,       LSFT(KC_NUHS),
        KC_TRNS, LSFT(KC_NUBS), KC_GRAVE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_GRV), LSFT(KC_NUBS), KC_TRNS,
        KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN,      KC_PGUP,       KC_END),

    [_RAISE] = LAYOUT_ortho_4x12(
        KC_VOLU, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_LBRC, KC_RBRC, KC_MINS, KC_EQL,  KC_NUHS,
        KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_APP,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_GRV,  KC_NUBS, KC_TRNS,
        KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT),

    [_ADJUST] = LAYOUT_ortho_4x12(
        KC_TRNS, RGB_TOG,     RGB_MOD, RGB_HUD, RGB_HUI,  RGB_SAD,  RGB_SAI, RGB_VAD, RGB_VAI, KC_TRNS, KC_TRNS, QK_BOOT,
        KC_TRNS, RGB_M_P,     RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, KC_TRNS, KC_TRNS,
        KC_TRNS, TG(_NUMPAD), KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

const rgblight_segment_t PROGMEM _RAISE_lighting[] = RGBLIGHT_LAYER_SEGMENTS(
    {7, 1, 1, 202, 110}
);
const rgblight_segment_t PROGMEM _LOWER_lighting[] = RGBLIGHT_LAYER_SEGMENTS(
    {7, 1, 125, 188, 80}
);
const rgblight_segment_t PROGMEM _ADJUST_lighting[] = RGBLIGHT_LAYER_SEGMENTS(
    {7, 1, 32, 25, 127}
);
const rgblight_segment_t PROGMEM _NUMPAD_lighting[] = RGBLIGHT_LAYER_SEGMENTS(
    {7, 1, HSV_BLUE}
);
const rgblight_segment_t PROGMEM _DEFAULT_lighting[] = RGBLIGHT_LAYER_SEGMENTS(
    {7, 1, HSV_OFF}
);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    _DEFAULT_lighting,
    _NUMPAD_lighting,
    _LOWER_lighting,
    _RAISE_lighting,
    _ADJUST_lighting
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;

    // Uncomment for debug mode
    //debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    rgblight_set_layer_state(_QWERTY, layer_state_cmp(state, _QWERTY));
    rgblight_set_layer_state(_NUMPAD, layer_state_cmp(state, _NUMPAD));
    rgblight_set_layer_state(_LOWER, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(_RAISE, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(_ADJUST, layer_state_cmp(state, _ADJUST));

    return state;
}

#ifdef ENCODER_MAP_ENABLE
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
        [_NUMPAD] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
        [_LOWER] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
        [_RAISE] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
        [_ADJUST] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    };
#endif
