/* Copyright 2021 Felix Springer
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

enum layers_user {
    _QWERTY,
    _AD,
    _VI,
    _FN,
    _KB
};

enum keycodes_user {
    _BASEEF = SAFE_RANGE,
    _KITTEF
};

int selected_mode_user = RGB_MATRIX_CUSTOM_base_effect; // for layer_state_set_user()
bool process_record_user(uint16_t keycode, keyrecord_t * record) {
    switch (keycode) {
        case _BASEEF:
            if (record->event.pressed) {
                selected_mode_user = RGB_MATRIX_CUSTOM_base_effect;
            }
            return false;
        case _KITTEF:
            if (record->event.pressed) {
                selected_mode_user = RGB_MATRIX_CUSTOM_kitt_effect;
            }
            return false;
        default:
            return true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_65_ansi(
        KC_GRAVE,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_ESC,         KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL,        KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_AD] = LAYOUT_65_ansi(
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_HOME,
        _______,                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_END,
        _______,        _______, _______,                            _______,                   _______, _______, _______, _______, _______, _______
    ),
    [_VI] = LAYOUT_65_ansi(
        KC_ESC,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_ESC,         XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,          _______, XXXXXXX,
        _______,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_FIND, _______, _______, XXXXXXX,
        _______,        _______, _______,                            _______,                   _______, _______, _______, _______, _______, _______
    ),
    [_FN] = LAYOUT_65_ansi(
        XXXXXXX,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,
        XXXXXXX,        KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_SCRL, KC_PAUS, XXXXXXX, KC_PSTE,
        CTL_T(KC_CAPS), KC_BRID, KC_VOLD, KC_BRIU, XXXXXXX, XXXXXXX, TG(_AD), TG(_VI), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, KC_COPY,
        KC_LSFT,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_APP,  XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT, KC_MSTP, KC_CUT,
        KC_LCTL,        KC_LGUI, KC_LALT,                            XXXXXXX,                   MO(_KB), XXXXXXX, KC_RCTL, KC_MPRV, KC_MPLY, KC_MNXT
    ),
    [_KB] = LAYOUT_65_ansi(
        XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, RGB_SPI, RGB_SPD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX,
        XXXXXXX,        RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,        XXXXXXX, RGB_SAI, RGB_SAD, XXXXXXX, XXXXXXX, _BASEEF, _KITTEF, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          EE_CLR,  XXXXXXX,
        KC_LSFT,                 RGB_VAI, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, NK_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT, XXXXXXX, XXXXXXX,
        XXXXXXX,        XXXXXXX, XXXXXXX,                            XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
    /*
    [_LEDS]    = LAYOUT_65_ansi(
         0  ,            1  ,     2  ,     3  ,     4  ,     5  ,     6  ,     7  ,     8  ,     9  ,    10  ,    11  ,    12  ,    13  ,    14  ,
        15  ,           16 Q,    17 W,    18 E,    19 R,    20 T,    21 Y,    22 U,    23 I,    24 O,    25 P,    26  ,    27  ,    28  ,    29  ,
        30  ,           31 A,    32 S,    33 D,    34 F,    35 G,    36 H,    37 J,    38 K,    39 L,    40  ,    41  ,             42  ,    43  ,
        44  ,                    45 Z,    46 X,    47 C,    48 V,    49 B,    50 N,    51 M,    52  ,    53  ,    54  ,    55  ,    56  ,    57  ,
        58  ,           59  ,    60  ,                               61  ,                      62  ,    63  ,    64  ,    65  ,    66  ,    67
    )
    */
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _QWERTY:
            rgb_matrix_mode(selected_mode_user);
            break;
        case _AD:
            if (selected_mode_user == RGB_MATRIX_CUSTOM_base_effect) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_base_ad_effect);
            } else {
                rgb_matrix_mode(selected_mode_user);
            }
            break;
        case _VI:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_vi_effect);
            break;
        case _FN:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_fn_indicator);
            break;
        case _KB:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_kb_indicator);
            break;
    }

    return state;
}
