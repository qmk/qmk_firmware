/* Copyright 2022 DOIO
 * Copyright 2022 DOIO2022 <https://github.com/DOIO2022>
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

enum layer_names {
    _LAY0,
    _LAY1,
    _LAY2,
    _LAY3,
    _LAY4,
    _LAY5
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_LAY0] = LAYOUT(
            TO(1),      RGB_MOD,        RGB_TOG,        RGB_HUI,        RGB_VAD,        RGB_VAI,    
                KC_MPLY,                                    KC_UP,                                      KC_UP,
    KC_MNXT,    KC_TRNS,    KC_MPRV,        A(KC_LEFT),     KC_TRNS,    A(KC_RIGHT),        KC_RIGHT,   KC_TRNS,    KC_LEFT,
                KC_MPLY,                                    KC_DOWN,                                    KC_DOWN),
    [_LAY1] = LAYOUT(
            TO(2),      KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,    
                KC_WH_U,                                    S(KC_RBRC),                                 C(KC_L),
    C(KC_WH_D), KC_TRNS,    C(KC_WH_U),     KC_DOT,         KC_TRNS,    KC_COMM,            C(KC_B),    KC_TRNS,    C(KC_U),
                KC_WH_D,                                    S(KC_LBRC),                                 C(KC_M)),
    [_LAY2] = LAYOUT(
            TO(3),      KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,    
                KC_B,                                       KC_UP,                                      S(KC_I),
    KC_P,       KC_TRNS,    KC_H,           KC_RIGHT,       KC_TRNS,    KC_LEFT,            KC_O,       KC_TRNS,    KC_I,
                KC_Y,                                       KC_DOWN,                                    S(KC_O)),
    [_LAY3] = LAYOUT(
            TO(4),      KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,    
                KC_TRNS,                                    KC_TRNS,                                    KC_TRNS,
  KC_TRNS,      KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,                                    KC_TRNS,                                    KC_TRNS),
    [_LAY4] = LAYOUT(
            TO(5),      KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,   
                KC_TRNS,                                    KC_TRNS,                                    KC_TRNS,
  KC_TRNS,      KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,                                    KC_TRNS,                                    KC_TRNS),
    [_LAY5] = LAYOUT(
		   TO(0),      KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS, 
                KC_TRNS,                                    KC_TRNS,                                    KC_TRNS,
  KC_TRNS,      KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,                                    KC_TRNS,                                    KC_TRNS),

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_LAY0] = { ENCODER_CCW_CW(C(KC_DOWN), C(KC_UP)), ENCODER_CCW_CW(C(KC_PMNS), C(KC_PPLS)), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LAY1] = { ENCODER_CCW_CW(C(KC_PMNS), C(KC_PPLS)), ENCODER_CCW_CW(KC_LBRC, KC_RBRC), ENCODER_CCW_CW(C(S(KC_U)), C(KC_I)) },
    [_LAY2] = { ENCODER_CCW_CW(KC_C, KC_V), ENCODER_CCW_CW(KC_MINS, KC_EQL), ENCODER_CCW_CW(KC_J, KC_L) },
    [_LAY3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY4] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY5] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
