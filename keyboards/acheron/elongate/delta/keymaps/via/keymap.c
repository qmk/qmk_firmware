/* Copyright 2020 Gondolindrim
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
#define SPC_L2 LT(2, KC_SPACE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_all( /* Base */
    KC_ESC , KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,  KC_KP_7,  KC_KP_8, KC_KP_9,
    KC_TAB , KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,             KC_ENTER, KC_KP_4,  KC_KP_5, KC_KP_6,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, MO(1)  , KC_UP,    KC_KP_1,  KC_KP_2, KC_KP_3,
    KC_LCTL, KC_LWIN, KC_LALT,          SPC_L2,                    KC_SPC,           KC_RALT, KC_LEFT, KC_DOWN,  KC_RIGHT, KC_KP_0, KC_DOT
),
[1] = LAYOUT_all( /* Base */
    KC_F1,   KC_F2,   KC_F2,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_LBRC, KC_RBRC, KC_MINS,  KC_EQL,  KC_NLCK, KC_SLCK, KC_CAPS,
    KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_RSFT, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SCLN, KC_QUOT, KC_SLSH, KC_TRNS,  KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,                   KC_SPC,           KC_TRNS, KC_HOME,  KC_PGDN, KC_END , KC_TRNS, KC_TRNS
),
[2] = LAYOUT_all( /* Base */                                    
    QK_BOOT  , KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,          RGB_TOG, RGB_MOD,  RGB_RMOD, RGB_M_T, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS ,                   KC_SPC,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
[3] = LAYOUT_all( /* Base */                                    
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,          KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,                   KC_SPC,           KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
)
};
