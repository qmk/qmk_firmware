/*
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

#define _FUNC       MO(_FNCLASSIC)
#define _SHENT      RSFT_T(KC_ENT)
#define _LSNUBS     LSFT_T(KC_NUBS)
#define _AGRSPC     RALT_T(KC_SPC)


// Layer shorthand
enum layer_names {
    _CLASSIC,
    _FNCLASSIC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Base Layer
     * .--------------------------------------------------------------.        .--------------------------------------------------------------.
     * | ESC    | 1      | 2      | 3      | 4      | 5      | -      |        | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
     * |--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     * | TAB    | Q      | W      | E      | R      | T      | [      |        | ]      | Y      | U      | I      | O      | P      | |\     |
     * |--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     * | LCTRL  | A      | S      | D      | F      | G      | HOME   |        | PG UP  | H      | J      | K      | L      | ;      | '      |
     * |--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     * | LSHIFT | Z      | X      | C      | V      | B      | END    |        | PG DN  | N      | M      | ,      | .      | /      | SH/ENT |
     * '--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------'
     *          | LGUI   | DEL    | ~`     | LALT   | SPACE  |        | FN     | SPACE  |        | LEFT   | DOWN   | UP     | RIGHT  |
     *          '--------------------------------------------------------------------------------------------------------------------'
     */
    [_CLASSIC] = LAYOUT_classic(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS,           KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,           KC_RBRC, KC_Y,	   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME,           KC_PGUP, KC_H,	   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_END,            KC_PGDN, KC_N,	   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _SHENT,
                 KC_LGUI, KC_DEL,  KC_GRV,  KC_LALT, KC_SPC,  KC_SPC,  _FUNC,    _AGRSPC, _AGRSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    /* Function Layer
	 * .--------------------------------------------------------------.        .--------------------------------------------------------------.
     * | QK_BOOT  | F1     | F2     | F3     | F4     | F5     | F11    |        | F12    | F6     | F7     | F8     | F9     | F10    | DEL    |
     * |--------+--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+--------|
     * |        |        | MENU   |        | QK_BOOT  |        |        |        |        |        |        | INS    |        | PRT SC |        |
     * |--------+--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+--------|
     * | CAPSLK |        | SCROLL |        |        |        |        |        |        |        |        |        |        |        | RCTL   |
     * |--------+--------+--------+--------+--------+--------+--------+        +--------+--------+--------+--------+--------+--------+--------|
     * | UK \|  |        |        |        |        | PAUSE  |        |        |        |        | MUTE   | VOL DN | VOL UP |        |        |
     * '--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+--------+--------+--------'
     *          | RGUI   |        |        | RALT   |                 |        |                 |        |        |        |        |
     *          '--------------------------------------------------------------------------------------------------------------------'
     */
    [_FNCLASSIC] = LAYOUT_classic(
        QK_BOOT,    KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,           KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, _______, KC_APP,  _______, QK_BOOT,   _______, _______,          _______, _______, _______, KC_INS,  _______, KC_PSCR, _______,
        KC_CAPS, _______, KC_SCRL, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, KC_RCTL,
        _LSNUBS, _______, _______, _______, _______, KC_PAUS, _______,          _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
                 KC_RGUI, _______, _______, KC_RALT, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};
