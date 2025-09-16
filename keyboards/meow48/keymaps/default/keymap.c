/* Copyright 2022 tsubuan145
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
 
 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────────┐
     * │Esc │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ - │  BSPACE│
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │Tab   │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │     Enter│
     * ├──────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬─────────┤
     * │Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift│
     * ├─────┬─┴─┬─┴─┬─┴─┬─┴───┴─┬─┴───┴─┬─┴─┬─┴──┬┴───┼────┬────┤
     * │Caps │CTL│GUI│Alt│       │       │Del│LEFT│ UP │DOWN│RGHT│
     * └─────┴───┴───┴───┴───────┴───────┴───┴────┴────┴────┴────┘
     * 
     */
     
     [0] = LAYOUT(
        KC_ESCAPE,  LT(3,KC_Q),    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, KC_BSPC,
        KC_TAB,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,          KC_ENT,
        KC_LSFT,    KC_Z,    LT(2,KC_X),    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,    KC_RSFT,
        KC_CAPS,    KC_LCTL, KC_LGUI, KC_LALT,    KC_SPACE,               LT(1, KC_SPACE),   KC_DEL,  KC_LEFT, KC_UP,  KC_DOWN, KC_RGHT
    ),
    
     [1] = LAYOUT(
        KC_NO,  LSFT(KC_1),    LSFT(KC_2),    LSFT(KC_3),    LSFT(KC_4),    LSFT(KC_5),    LSFT(KC_6),    LSFT(KC_7),    LSFT(KC_8),    LSFT(KC_9),  KC_LBRC, KC_CIRC, KC_BSPC,
        KC_NO,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,          KC_ENT,
        KC_LSFT,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PLUS, KC_INT3, KC_INT1,       KC_RSFT,
        KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,  KC_DEL,  KC_LEFT, KC_UP, KC_DOWN, KC_RGHT
    ),
    
     [2] = LAYOUT(
        KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12, KC_NO,
        KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,         KC_NO,
        KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,         KC_NO,
        KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,   UG_TOGG,   UG_HUED,  UG_HUEU,  UG_PREV,  UG_NEXT
    ),
    
     [3] = LAYOUT(
        KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,  KC_NO,
        KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,           KC_NO,
        KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,           KC_NO,
        KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,              KC_NO,    KC_NO,    KC_NO,   KC_NO,  KC_NO
    )
    
        };
