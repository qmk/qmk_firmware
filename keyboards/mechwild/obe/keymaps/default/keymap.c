/* Copyright 2021 Kyle McCreery
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
	_FN2,
	_FN3
};
/*
    k45, k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k2c, k0d, \
    k47, k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      k1d, \
    k42, k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,           k2d, \
         k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,      k3d, \
         k40, k41,      k43, k44,      k46,      k48, k49, k4a, k4b, k4c,      k4d  \
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
    KC_MUTE, KC_ESC,  KC_1,    KC_2, KC_3,    KC_4,   KC_5, KC_6,   KC_7, KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_TRNS, KC_BSPC,
    KC_F1,   KC_TAB,  KC_Q,    KC_W, KC_E,    KC_R,   KC_T, KC_Y,   KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS,
    KC_F2,   MO(1),   KC_A,    KC_S, KC_D,    KC_F,   KC_G, KC_H,   KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,
             KC_LSFT, KC_Z,    KC_X, KC_C,    KC_V,   KC_B, KC_B,   KC_N, KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_UP,   KC_RSFT,
             KC_LCTL, KC_LGUI,       KC_LALT, KC_SPC,       KC_SPC,       KC_RALT, MO(2),   KC_RCTL, KC_LEFT, KC_DOWN, KC_UP
    ),
    [_FN1] = LAYOUT(                                                                                   
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_FN2] = LAYOUT(                                                                                   
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_FN3] = LAYOUT(                                                                                   
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case 0:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        break;
    }
}
#endif
